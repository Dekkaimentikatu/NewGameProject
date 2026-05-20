#include "thread_pool/thread_pool.h"

C_THREAD_POOL::C_THREAD_POOL(size_t threadCount)
{
	for (size_t i = 0; i < threadCount; ++i)
	{
		//末尾に追加
		m_workers.emplace_back(&C_THREAD_POOL::WorkerLoop, this);
	}
}

C_THREAD_POOL::~C_THREAD_POOL()
{

	//m_jobsMutexへのアクセスを制限
	lock_guard<mutex> lock(m_jobsMutex);

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
		//m_jobsMutexへのアクセスを制限
		lock_guard<mutex> lock(m_jobsMutex);

		//引数で渡された関数を追加
		m_jobs.push(move(job));
	}

	//スレッドを起動
	m_cv.notify_one();
}

void C_THREAD_POOL::WorkerLoop()
{
	while (true)
	{
		function<void()> job;

		//スレッド待機処理
		{
			//m_jobsMutexへのアクセスを制限
			unique_lock<mutex> lock(m_jobsMutex);

			//スレッドが起床するまで待機
			m_cv.wait(lock, [this]
				{
					return m_stop || !m_jobs.empty();
				});

			//タスクがないなら何もしない
			if (m_stop && m_jobs.empty())
			{
				return;
			}

			//先頭要素を取得
			job = move(m_jobs.front());

			//先頭要素を削除
			m_jobs.pop();
		}

		//タスク実行
		job();
	}
}