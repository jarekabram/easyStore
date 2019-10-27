#ifndef _THREAD_MANAGER_
#define _THREAD_MANAGER_

#include <thread>
#include <functional>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

class ThreadManager
{
	bool m_shutdown;
	// handle to thread
	std::unique_ptr<std::thread> m_thread;
	// queue for functions that have to be invoked
	std::queue<std::function<void(void)>> m_tasks;

	std::mutex m_taskMutex;
	std::condition_variable m_conditionalVariable;
	
public:
	// removed copy constructor and assign operator
	ThreadManager(const ThreadManager&) = delete;
	ThreadManager& operator=(const ThreadManager&) = delete;

	// ctors and dtors
	ThreadManager();
	~ThreadManager();

	void runTask(std::function <void(void)> func);
	void entry();

};

#endif // _THREAD_MANAGER_