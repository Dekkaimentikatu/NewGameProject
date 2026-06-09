#include "thread_pool/thread_pool.h"

//コンストラクタ
C_THREAD_POOL::C_THREAD_POOL(size_t threadCount)
{
	//ワーカースレッドを生成
	for (size_t i = 0; i < threadCount; ++i)
	{
		//ワーカースレッドを生成してループを開始
		m_workers.emplace_back(
			&C_THREAD_POOL::WorkerLoop,
			this);
	}
}

//デストラクタ
C_THREAD_POOL::~C_THREAD_POOL()
{
	//すべてのタスクが完了するまで待機
	Wait();
	//停止フラグを立てる
	m_stop.store(true);
	//条件変数を通知してワーカースレッドを起こす
	m_cv.notify_all();

	for (auto& worker : m_workers)
	{
		//ワーカースレッドが結合可能なら結合
		if (worker.joinable())
		{
			//ワーカースレッドを結合
			worker.join();
		}
	}
}

//ワーカーループ
void C_THREAD_POOL::WorkerLoop()
{
	while (true)
	{
		//タスクを取得
		std::function<void()> task;

		//タスクがあれば実行
		if (m_tasks.Pop(task))
		{
			//タスクを実行
			task();

			//実行中タスク数を減らす
			m_activeTask.fetch_sub(
				1,
				std::memory_order_release);
		}
		//タスクがなければ待機
		else
		{
			//ミューテックスをロック
			std::unique_lock<std::mutex> lock(
				m_waitMutex);

			//停止フラグが立っていないか、実行中タスク数が0でない限り待機
			m_cv.wait(lock, [this]
				{
					return
						m_stop.load(
							std::memory_order_acquire)
						||
						m_activeTask.load(
							std::memory_order_acquire) > 0;
				});

			//停止フラグが立っていればループを抜ける
			if (m_stop.load(
				std::memory_order_acquire))
			{
				return;
			}
		}
	}
}

//エンキュー
void C_THREAD_POOL::Enqueue(std::function<void()> job)
{
	//実行中タスク数を増やす
	m_activeTask.fetch_add(
		1,
		std::memory_order_release);

	//タスクをキューに登録
	m_tasks.Push(std::move(job));

	//条件変数を通知してワーカースレッドを起こす
	m_cv.notify_one();
}

//待機
void C_THREAD_POOL::Wait()
{
	//すべてのタスクが完了するまで待機
	while (
		m_activeTask.load(
			std::memory_order_acquire) > 0)
	{
		//タスクが完了するのを待つ
		std::this_thread::yield();
	}
}