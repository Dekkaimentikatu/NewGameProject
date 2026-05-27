#pragma once

#include <vector>
#include <thread>
#include <atomic>
#include <functional>
#include <iostream>

// ============================================================
// ABA対策付き Lock-Free Thread Pool
//
// 改良点
// ・Tagged Pointer による ABA対策
// ・memory_order整理
// ・deleteを行わない安全設計
// ・false sharing軽減
// ============================================================

class C_THREAD_POOL
{
private:

    // ========================================================
    // Cache Line Padding
    // ========================================================
    struct alignas(64) CACHE_ALIGN
    {
    };

    // ========================================================
    // Tagged Pointer
    // ABA対策
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
    // Michael & Scott Queue
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

        alignas(64)
            std::atomic<TaggedPtr<Node>> m_head;

        alignas(64)
            std::atomic<TaggedPtr<Node>> m_tail;

    public:

        LockFreeQueue()
        {
            Node* dummy = new Node();

            TaggedPtr<Node> ptr(dummy, 0);

            m_head.store(ptr, std::memory_order_release);
            m_tail.store(ptr, std::memory_order_release);
        }

        ~LockFreeQueue()
        {
            // 学習用安全設計
            // lock-free delete問題回避

            TaggedPtr<Node> current =
                m_head.load(std::memory_order_acquire);

            while (current.ptr)
            {
                TaggedPtr<Node> next =
                    current.ptr->next.load(std::memory_order_acquire);

                delete current.ptr;

                current = next;
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
                    tail.ptr->next.load(std::memory_order_acquire);

                // tail整合性確認
                if (tail == m_tail.load(std::memory_order_acquire))
                {
                    // 最後尾
                    if (next.ptr == nullptr)
                    {
                        TaggedPtr<Node> newNext(
                            newNode,
                            next.tag + 1);

                        // next更新
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
                        // tail進行
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
                    head.ptr->next.load(std::memory_order_acquire);

                // head整合性確認
                if (head == m_head.load(std::memory_order_acquire))
                {
                    // 空
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

                    result = std::move(next.ptr->data);

                    TaggedPtr<Node> newHead(
                        next.ptr,
                        head.tag + 1);

                    if (m_head.compare_exchange_weak(
                        head,
                        newHead,
                        std::memory_order_release,
                        std::memory_order_relaxed))
                    {
                        // =================================================
                        // ABA安全化のため deleteしない
                        // =================================================
                        return true;
                    }
                }
            }
        }
    };

private:

    // ========================================================
    // メンバ
    // ========================================================

    std::vector<std::thread> m_workers;

    LockFreeQueue<std::function<void()>> m_tasks;

    alignas(64)
        std::atomic<bool> m_stop = false;

    alignas(64)
        std::atomic<int> m_activeTask = 0;

private:

    // ========================================================
    // Worker Loop
    // ========================================================
    void WorkerLoop()
    {
        while (!m_stop.load(std::memory_order_acquire))
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
                std::this_thread::yield();
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

        m_stop.store(
            true,
            std::memory_order_release);

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
    }

    // ========================================================
    // Wait
    // ========================================================
    void Wait()
    {
        while (
            m_activeTask.load(std::memory_order_acquire) > 0)
        {
            std::this_thread::yield();
        }
    }
};