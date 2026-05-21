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
    //スレッド管理用配列
    vector<thread> m_workers;

    //タスク管理用キュー
    queue<function<void()>> m_task;

    //起動しているタスク数
    atomic<int> m_activetask = 0;

    //ミューテックス
    mutex m_taskMutex;

    //スレッド停止
    condition_variable m_cv;

    //停止フラグ
    bool m_stop = false;

    //実行処理ループ
    void WorkerLoop();

public:

    //コンストラクタ
    //スレッド数を指定
    C_THREAD_POOL(size_t threadCount);

    //デストラクタ
    ~C_THREAD_POOL();

    //キューに追加
    void Enqueue(function<void()> job);

    //待機
    void Wait();
};