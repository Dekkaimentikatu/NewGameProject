//#include "_thread_pool.h"
//
////============================================================
//// Worker Loop
////============================================================
//void C_THREAD_POOL::WorkerLoop()
//{
//	while (!m_stop.load(std::memory_order_acquire))
//	{
//		std::function<void()> task;
//
//		if (m_tasks.Pop(task))
//		{
//			task();
//
//			--m_activeTask;
//		}
//		else
//		{
//			// É^ÉXÉNÇ™Ç»Ç¢ÇÃÇ≈CPUè˜ìn
//			std::this_thread::yield();
//		}
//	}
//}
//
////============================================================
//// Constructor
////============================================================
//C_THREAD_POOL::C_THREAD_POOL(size_t threadCount)
//{
//	for (size_t i = 0; i < threadCount; ++i)
//	{
//		m_workers.emplace_back(
//			&C_THREAD_POOL::WorkerLoop,
//			this);
//	}
//}
//
////============================================================
//// Destructor
////============================================================
//C_THREAD_POOL::~C_THREAD_POOL()
//{
//	Wait();
//
//	m_stop.store(true, std::memory_order_release);
//
//	for (auto& worker : m_workers)
//	{
//		if (worker.joinable())
//		{
//			worker.join();
//		}
//	}
//}
//
////============================================================
//// Enqueue
////============================================================
//void C_THREAD_POOL::Enqueue(std::function<void()> job)
//{
//	++m_activeTask;
//
//	m_tasks.Push(std::move(job));
//}
//
////============================================================
//// Wait
////============================================================
//void C_THREAD_POOL::Wait()
//{
//	while (m_activeTask.load(std::memory_order_acquire) > 0)
//	{
//		std::this_thread::yield();
//	}
//}