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
	struct T_TAGGED_PTR
	{
		//テンプレート型ポインタ変数
		T* ptr;
		//符号無し64ビット整数型変数
		uint64_t tag;

		//コンストラクタ
		T_TAGGED_PTR(T* p = nullptr, uint64_t t = 0)
			: ptr(p), tag(t)
		{
		}

		//==の定義
		bool operator==(const T_TAGGED_PTR& other) const
		{
			return ptr == other.ptr &&
				tag == other.tag;
		}
	};

	template<typename T>
	//ロックフリーキュークラス
	class C_LOCK_FREE_QUEUE
	{
	private:

		//ノード
		struct Node
		{
			//テンプレート型変数
			T data;
			//キューの次の要素
			std::atomic<T_TAGGED_PTR<Node>> next;

			//コンストラクタ
			Node()
				: next(T_TAGGED_PTR<Node>(nullptr, 0))
			{
			}

			//コンストラクタ(値を代入)
			Node(T value)
				: data(std::move(value)),
				next(T_TAGGED_PTR<Node>(nullptr, 0))
			{
			}
		};

		//キューの先頭
		std::atomic<T_TAGGED_PTR<Node>> m_head;
		//キューの末尾
		std::atomic<T_TAGGED_PTR<Node>> m_tail;

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
		C_LOCK_FREE_QUEUE()
		{
			//ダミーのノードを生成
			Node* dummy = new Node();
			//ターゲットに登録
			T_TAGGED_PTR<Node> ptr(dummy, 0);
			//先頭と末尾に登録
			m_head.store(ptr);
			m_tail.store(ptr);
		}

		//デストラクタ
		~C_LOCK_FREE_QUEUE()
		{
			// queue側解放
			T_TAGGED_PTR<Node> current =
				m_head.load(std::memory_order_acquire);

			//解放処理
			while (current.ptr)
			{
				T_TAGGED_PTR<Node> next =
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
				T_TAGGED_PTR<Node> tail =
					m_tail.load(std::memory_order_acquire);

				//最後尾を参照
				T_TAGGED_PTR<Node> next =
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
						T_TAGGED_PTR<Node> newNext(
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
							T_TAGGED_PTR<Node> newTail(
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
						T_TAGGED_PTR<Node> newTail(
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
				T_TAGGED_PTR<Node> head =
					m_head.load(std::memory_order_acquire);

				T_TAGGED_PTR<Node> tail =
					m_tail.load(std::memory_order_acquire);

				T_TAGGED_PTR<Node> next =
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
					T_TAGGED_PTR<Node> newTail(
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

				T_TAGGED_PTR<Node> newHead(
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

	//ワーカースレッド
	std::vector<std::thread> m_workers;
	//タスクキュー
	C_LOCK_FREE_QUEUE<std::function<void()>> m_tasks;

	//停止フラグ
	std::atomic<bool> m_stop = false;
	//実行中タスク数
	std::atomic<int> m_activeTask = 0;

	//待機用ミューテックス
	std::mutex m_waitMutex;
	//待機用条件変数
	std::condition_variable m_cv;

private:

	//ワーカーループ
	void WorkerLoop();

public:

	//コンストラクタ
	C_THREAD_POOL(size_t threadCount);

	//デストラクタ
	~C_THREAD_POOL();

	//エンキュー
	void Enqueue(std::function<void()> job);

	//待機
	void Wait();
};

