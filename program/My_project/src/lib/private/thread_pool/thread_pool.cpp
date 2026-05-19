#include "thread_pool/thread_pool.h"

C_THREAD_POOL::C_THREAD_POOL(size_t threadCount)
{
    for (size_t i = 0; i < threadCount; ++i)
    {
        workers.emplace_back(
            &C_THREAD_POOL::WorkerLoop,
            this);
    }
}

C_THREAD_POOL::~C_THREAD_POOL()
{
    {
        lock_guard<mutex> lock(jobsMutex);

        stop = true;
    }

    cv.notify_all();

    for (auto& worker : workers)
    {
        worker.join();
    }
}

void C_THREAD_POOL::Enqueue(
    function<void()> job)
{
    {
        lock_guard<mutex> lock(jobsMutex);

        jobs.push(move(job));
    }

    cv.notify_one();
}

void C_THREAD_POOL::WorkerLoop()
{
    while (true)
    {
        std::function<void()> job;

        {
            unique_lock<mutex> lock(jobsMutex);

            cv.wait(lock, [this]
                {
                    return stop || !jobs.empty();
                });

            if (stop && jobs.empty())
            {
                return;
            }

            job = std::move(jobs.front());

            jobs.pop();
        }

        job();
    }
}