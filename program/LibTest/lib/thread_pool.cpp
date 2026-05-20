#include "thread_pool.h"

C_THREAD_POOL::C_THREAD_POOL(size_t threadCount)
{
	//スレッドを確保
	for (size_t i = 0; i < threadCount; ++i)
	{
		//末尾に追加
		m_workers.emplace_back(&C_THREAD_POOL::WorkerLoop, this);
	}
}

C_THREAD_POOL::~C_THREAD_POOL()
{

	//m_taskMutexへのアクセスを制限
	lock_guard<mutex> lock(m_taskMutex);

	//スレッド停止
	m_stop = true;

	//全ての待機中スレッドを起動
	m_cv.notify_all();

	//全ての処理が終了するまで待機
	for (auto& worker : m_workers)
	{
		worker.join();
	}
}

void C_THREAD_POOL::Enqueue(function<void()> job)
{
	//Enqueue処理
	{
		//m_taskMutexへのアクセスを制限
		lock_guard<mutex> lock(m_taskMutex);

		//引数で渡された関数を追加
		m_task.push(move(job));

		++m_activetask;
	}

	//スレッドを起動
	m_cv.notify_one();
}

void C_THREAD_POOL::WorkerLoop()
{
	while (true)
	{
		function<void()> task;

		//スレッド待機処理
		{
			//m_jobsMutexへのアクセスを制限
			unique_lock<mutex> lock(m_taskMutex);

			//スレッドが起床するまで待機
			m_cv.wait(lock, [this]
				{
					return m_stop || !m_task.empty();
				});

			//タスクがないなら何もしない
			if (m_stop && m_task.empty())
			{
				return;
			}

			//先頭要素を取得
			task = move(m_task.front());

			//先頭要素を削除
			m_task.pop();
		}

		//タスク実行
		task();

		--m_activetask;
	}
}

void C_THREAD_POOL::Wait()
{
	//タスク数が０より多い間
	while (m_activetask > 0)
	{
		//現在実行中のスレッドとは別のスレッドに処理を行わせる
		this_thread::yield();
	}
}