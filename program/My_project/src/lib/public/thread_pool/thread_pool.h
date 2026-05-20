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

    //コンストラクタ
    //スレッド数を指定
    C_THREAD_POOL(size_t threadCount);

    //デストラクタ
    ~C_THREAD_POOL();

    //キューに追加
    void Enqueue(function<void()> job);

private:

    void WorkerLoop();

private:

    //タスク管理用配列
    vector<thread> m_workers;

    //タスク管理用キュー
    queue<function<void()>> m_jobs;

    //ミューテックス
    mutex m_jobsMutex;

    //スレッド停止
    condition_variable m_cv;

    //停止フラグ
    bool m_stop = false;
};