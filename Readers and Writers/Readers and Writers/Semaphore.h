#pragma once
#include <condition_variable>
#include <mutex>

using namespace std;

struct Semaphore
{
public:
	Semaphore() {};
	Semaphore(int i)
	{
		m_count = i;
	}

	int m_count;
	mutex m_mutex;
	condition_variable m_cv;
};

static void P(Semaphore& sem)
{
	unique_lock<decltype(sem.m_mutex)> m_lock(sem.m_mutex);
	while (sem.m_count <= 0)
	{
		sem.m_cv.wait(m_lock);
	}
	sem.m_count--;
}

static void V(Semaphore& sem)
{
	unique_lock<decltype(sem.m_mutex)> m_lock(sem.m_mutex);
	sem.m_count++;
	sem.m_cv.notify_one();
}