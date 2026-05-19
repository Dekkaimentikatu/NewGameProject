#pragma once
#pragma once

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

using namespace std;

class C_THREAD_POOL
{
public:

    C_THREAD_POOL(size_t threadCount);

    ~C_THREAD_POOL();

    void Enqueue(std::function<void()> job);

private:

    void WorkerLoop();

private:

    std::vector<std::thread> workers;

    std::queue<std::function<void()>> jobs;

    std::mutex jobsMutex;

    std::condition_variable cv;

    bool stop = false;
};