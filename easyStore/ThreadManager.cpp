#include "ThreadManager.h"

ThreadManager::ThreadManager() : m_shutdown(false)
{
	// create one unique thread that will run multiple
	m_thread = std::unique_ptr<std::thread>(new std::thread(std::bind(&ThreadManager::entry, this)));
}

void ThreadManager::runTask(std::function<void(void)> func)
{
	// Place a job on the queu and unblock a thread
	std::unique_lock <std::mutex> lock(m_taskMutex);

	m_tasks.emplace(std::move(func));
	m_conditionalVariable.notify_one();
	lock.unlock();
}

void ThreadManager::entry() 
{
	std::function<void(void)> task;

	while ( true )
	{
		std::unique_lock<std::mutex> lock(m_taskMutex);

		while (!m_shutdown && m_tasks.empty())
		{
			m_conditionalVariable.wait(lock);
		}

		if (m_tasks.empty())
		{
			// No jobs to do and we are shutting down
			std::cout << "Thread " << std::this_thread::get_id() << " terminates" << std::endl;
			return;
		}

		std::cout << "Thread " << std::this_thread::get_id() << " does a job" << std::endl;
		task = std::move(m_tasks.front());
		m_tasks.pop();

		// we have to run job between locks because we are using some resources that can be tried to used at the same time
		task();
		lock.unlock();
	}
}


ThreadManager::~ThreadManager() 
{
	// Unblock any threads and tell them to stop
	std::unique_lock<std::mutex> lock(m_taskMutex);

	m_shutdown = true;
	m_conditionalVariable.notify_all();
	lock.unlock();
}
