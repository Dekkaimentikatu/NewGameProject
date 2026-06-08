#pragma once

#include <vector>
#include <thread>
#include <atomic>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <cstdint>
#include <algorithm>
#include <utility>

class C_THREAD_POOL
{
private:

	//ターゲットポインター
	template<typename T>
	struct TaggedPtr
	{
		//テンプレート型ポインタ変数
		T* ptr;
		//符号無し64ビット整数型変数
		uint64_t tag;

		//コンストラクタ
		TaggedPtr(T* p = nullptr, uint64_t t = 0)
			: ptr(p), tag(t)
		{
		}

		//==の定義
		bool operator==(const TaggedPtr& other) const
		{
			return ptr == other.ptr &&
				tag == other.tag;
		}
	};

	template<typename T>
	//ロックフリーキュークラス
	class LockFreeQueue
	{
	private:

		//ノード
		struct Node
		{
			//テンプレート型変数
			T data;
			//キューの次の要素
			std::atomic<TaggedPtr<Node>> next;

			//コンストラクタ
			Node()
				: next(TaggedPtr<Node>(nullptr, 0))
			{
			}

			//コンストラクタ(値を代入)
			Node(T value)
				: data(std::move(value)),
				next(TaggedPtr<Node>(nullptr, 0))
			{
			}
		};

		//キューの先頭
		std::atomic<TaggedPtr<Node>> m_head;
		//キューの末尾
		std::atomic<TaggedPtr<Node>> m_tail;

		//安全削除用ミューテックス
		std::mutex m_deleteMutex;

		//削除待ちノード
		std::vector<Node*> m_retired;

	private:

		//削除待ちノードの排他処理
		void RetireNode(Node* node)
		{
			//ミューテックスをロック
			std::lock_guard<std::mutex> lock(m_deleteMutex);
			//削除待ち配列に登録
			m_retired.push_back(node);
		}

	public:

		//コンストラクタ
		LockFreeQueue()
		{
			//ダミーのノードを生成
			Node* dummy = new Node();
			//ターゲットに登録
			TaggedPtr<Node> ptr(dummy, 0);
			//先頭と末尾に登録
			m_head.store(ptr);
			m_tail.store(ptr);
		}

		//デストラクタ
		~LockFreeQueue()
		{
			// queue側解放
			TaggedPtr<Node> current =
				m_head.load(std::memory_order_acquire);

			//解放処理
			while (current.ptr)
			{
				TaggedPtr<Node> next =
					current.ptr->next.load(
						std::memory_order_acquire);

				delete current.ptr;

				current = next;
			}

			// retired解放
			for (Node* node : m_retired)
			{
				delete node;
			}
		}

		//登録
		void Push(T value)
		{
			//ノードを生成
			Node* newNode = new Node(std::move(value));

			while (true)
			{
				//末尾を取得
				TaggedPtr<Node> tail =
					m_tail.load(std::memory_order_acquire);

				//最後尾を参照
				TaggedPtr<Node> next =
					tail.ptr->next.load(
						std::memory_order_acquire);

				//比較
				if (tail ==
					m_tail.load(std::memory_order_acquire))
				{
					//最後尾がnull
					if (next.ptr == nullptr)
					{
						//最後尾のノードを生成
						TaggedPtr<Node> newNext(
							newNode,
							next.tag + 1);

						//最後尾と生成したノードを比較
						if (tail.ptr->next.compare_exchange_weak(
							next,
							newNext,
							std::memory_order_release,
							std::memory_order_relaxed))
						{
							//新しい末尾
							TaggedPtr<Node> newTail(
								newNode,
								tail.tag + 1);
							//末尾と新しい末尾を比較
							m_tail.compare_exchange_weak(
								tail,
								newTail,
								std::memory_order_release,
								std::memory_order_relaxed);

							return;
						}
					}
					else
					{
						//tail更新
						TaggedPtr<Node> newTail(
							next.ptr,
							tail.tag + 1);

						//バイトレベルで比較
						m_tail.compare_exchange_weak(
							tail,
							newTail,
							std::memory_order_release,
							std::memory_order_relaxed);
					}
				}
			}
		}

		//ポップ
		bool Pop(T& result)
		{
			while (true)
			{
				TaggedPtr<Node> head =
					m_head.load(std::memory_order_acquire);

				TaggedPtr<Node> tail =
					m_tail.load(std::memory_order_acquire);

				TaggedPtr<Node> next =
					head.ptr->next.load(
						std::memory_order_acquire);

				// empty
				if (next.ptr == nullptr)
				{
					return false;
				}

				// tail遅れ
				if (head.ptr == tail.ptr)
				{
					TaggedPtr<Node> newTail(
						next.ptr,
						tail.tag + 1);

					m_tail.compare_exchange_weak(
						tail,
						newTail,
						std::memory_order_release,
						std::memory_order_relaxed);

					continue;
				}

				//dataを先にローカルへコピー

				T value = next.ptr->data;

				TaggedPtr<Node> newHead(
					next.ptr,
					head.tag + 1);

				//head更新
				if (m_head.compare_exchange_weak(
					head,
					newHead,
					std::memory_order_release,
					std::memory_order_relaxed))
				{
					result = std::move(value);

					//即deleteしない
					RetireNode(head.ptr);

					return true;
				}
			}
		}
	};

private:

	// ========================================================
	// Thread
	// ========================================================

	std::vector<std::thread> m_workers;

	LockFreeQueue<std::function<void()>> m_tasks;

	// ========================================================
	// Atomic
	// ========================================================

	std::atomic<bool> m_stop = false;

	std::atomic<int> m_activeTask = 0;

	// ========================================================
	// Sleep
	// ========================================================

	std::mutex m_waitMutex;

	std::condition_variable m_cv;

private:

	// ========================================================
	// Worker
	// ========================================================
	void WorkerLoop()
	{
		while (true)
		{
			std::function<void()> task;

			if (m_tasks.Pop(task))
			{
				task();

				m_activeTask.fetch_sub(
					1,
					std::memory_order_release);
			}
			else
			{
				std::unique_lock<std::mutex> lock(
					m_waitMutex);

				m_cv.wait(lock, [this]
					{
						return
							m_stop.load(
								std::memory_order_acquire)
							||
							m_activeTask.load(
								std::memory_order_acquire) > 0;
					});

				if (m_stop.load(
					std::memory_order_acquire))
				{
					return;
				}
			}
		}
	}

public:

	// ========================================================
	// Constructor
	// ========================================================
	C_THREAD_POOL(size_t threadCount)
	{
		for (size_t i = 0; i < threadCount; ++i)
		{
			m_workers.emplace_back(
				&C_THREAD_POOL::WorkerLoop,
				this);
		}
	}

	// ========================================================
	// Destructor
	// ========================================================
	~C_THREAD_POOL()
	{
		Wait();

		m_stop.store(true);

		m_cv.notify_all();

		for (auto& worker : m_workers)
		{
			if (worker.joinable())
			{
				worker.join();
			}
		}
	}

	// ========================================================
	// Enqueue
	// ========================================================
	void Enqueue(std::function<void()> job)
	{
		m_activeTask.fetch_add(
			1,
			std::memory_order_release);

		m_tasks.Push(std::move(job));

		m_cv.notify_one();
	}

	// ========================================================
	// Wait
	// ========================================================
	void Wait()
	{
		while (
			m_activeTask.load(
				std::memory_order_acquire) > 0)
		{
			std::this_thread::yield();
		}
	}
};

