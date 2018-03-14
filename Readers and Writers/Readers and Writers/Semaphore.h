#pragma once

struct Semaphore
{
public:
	Semaphore() {};
	Semaphore(int i)
	{
		m_count = i;
	}

	int m_count;
};

static void P(Semaphore& sem)
{
	if (sem.m_count <= 0)
		sem.m_count--;
}

static void V(Semaphore& sem)
{
	sem.m_count++;
}