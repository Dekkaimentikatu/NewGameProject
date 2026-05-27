#pragma once

#include <vector>
#include <thread>
#include <atomic>
#include <functional>
#include <mutex>
#include <condition_variable>

class C_THREAD_POOL
{
private:

	// ========================================================
	// Tagged Pointer
	// ========================================================
	template<typename T>
	struct TaggedPtr
	{
		T* ptr;
		uint64_t tag;

		TaggedPtr(T* p = nullptr, uint64_t t = 0)
			: ptr(p), tag(t)
		{
		}

		bool operator==(const TaggedPtr& other) const
		{
			return ptr == other.ptr &&
				tag == other.tag;
		}
	};

	// ========================================================
	// LockFree Queue
	// ========================================================
	template<typename T>
	class LockFreeQueue
	{
	private:

		struct Node
		{
			T data;

			std::atomic<TaggedPtr<Node>> next;

			Node()
				: next(TaggedPtr<Node>(nullptr, 0))
			{
			}

			Node(T value)
				: data(std::move(value)),
				next(TaggedPtr<Node>(nullptr, 0))
			{
			}
		};

		// ====================================================
		// Queue
		// ====================================================

		std::atomic<TaggedPtr<Node>> m_head;
		std::atomic<TaggedPtr<Node>> m_tail;

		// ====================================================
		// Safe Delete
		// ====================================================

		std::mutex m_deleteMutex;

		std::vector<Node*> m_retired;

	private:

		// ====================================================
		// Retire
		// ====================================================
		void RetireNode(Node* node)
		{
			std::lock_guard<std::mutex> lock(m_deleteMutex);

			m_retired.push_back(node);
		}

	public:

		// ====================================================
		// Constructor
		// ====================================================
		LockFreeQueue()
		{
			Node* dummy = new Node();

			TaggedPtr<Node> ptr(dummy, 0);

			m_head.store(ptr);
			m_tail.store(ptr);
		}

		// ====================================================
		// Destructor
		// ====================================================
		~LockFreeQueue()
		{
			// queue側解放
			TaggedPtr<Node> current =
				m_head.load(std::memory_order_acquire);

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

		// ====================================================
		// Push
		// ====================================================
		void Push(T value)
		{
			Node* newNode = new Node(std::move(value));

			while (true)
			{
				TaggedPtr<Node> tail =
					m_tail.load(std::memory_order_acquire);

				TaggedPtr<Node> next =
					tail.ptr->next.load(
						std::memory_order_acquire);

				if (tail ==
					m_tail.load(std::memory_order_acquire))
				{
					// 最後尾
					if (next.ptr == nullptr)
					{
						TaggedPtr<Node> newNext(
							newNode,
							next.tag + 1);

						if (tail.ptr->next.compare_exchange_weak(
							next,
							newNext,
							std::memory_order_release,
							std::memory_order_relaxed))
						{
							TaggedPtr<Node> newTail(
								newNode,
								tail.tag + 1);

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
						// tail更新
						TaggedPtr<Node> newTail(
							next.ptr,
							tail.tag + 1);

						m_tail.compare_exchange_weak(
							tail,
							newTail,
							std::memory_order_release,
							std::memory_order_relaxed);
					}
				}
			}
		}

		// ====================================================
		// Pop
		// ====================================================
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

				// =================================================
				// dataを先にローカルへコピー
				// =================================================

				T value = next.ptr->data;

				TaggedPtr<Node> newHead(
					next.ptr,
					head.tag + 1);

				// head更新
				if (m_head.compare_exchange_weak(
					head,
					newHead,
					std::memory_order_release,
					std::memory_order_relaxed))
				{
					result = std::move(value);

					// =================================================
					// 即deleteしない
					// =================================================

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

