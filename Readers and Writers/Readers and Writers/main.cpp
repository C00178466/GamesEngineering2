#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <time.h>

using namespace std;

struct Semaphore
{
public:
	Semaphore() {};
	Semaphore(int i)
	{
		m_count = i;
	}

	//wait
	void P()
	{
		unique_lock<decltype(m_mutex)> lock(m_mutex);
		while (m_count <= 0)
		{
			m_cv.wait(lock);
		}
		m_count = m_count - 1;
	}

	//signal
	void V()
	{
		unique_lock<decltype(m_mutex)> lock(m_mutex);
		m_count = m_count + 1;
		m_cv.notify_one();
	}

private:
	mutex m_mutex;
	unique_lock<mutex> m_lock;
	condition_variable m_cv;
	int m_count;
};

//number of active readers
int nr = 0;

//Create Semaphores
Semaphore rw;
Semaphore rMutex;

void Reader()
{
	bool running = true;
	while (running)
	{
		rMutex.P(); // wait function on mutex
		nr++; //increase number of readers

		//Check if reader is the first one
		if (nr == 1)
		{
			rw.P(); // wait function

			cout << "Reader using File" << endl;
		}
		rMutex.V(); // signal function on mutex

		cout << "ID: " << this_thread::get_id() << endl;

		//Read from file here

		rMutex.P(); // wait function
		nr--; //decrease number of readers

		if (nr == 0)
		{
			cout << "Reader releasing File" << endl;
			rw.V();
		}
		rMutex.V(); // signal function on mutex

		this_thread::sleep_for(chrono::seconds(1));
	}
}

void Writer()
{
	bool running = true;
	while (running)
	{
		rw.P(); // wait function on mutex
		cout << "Writer using file" << endl;

		cout << "ID: " << this_thread::get_id() << endl;

		//write to file here

		cout << "Writer releasing file" << endl;
		rw.V(); // signal function on mutex

		this_thread::sleep_for(chrono::seconds(1));
	}
}


int main()
{
	//create 3 readers and 2 writers
	thread Reader1(Reader);
	thread Reader2(Reader);
	thread Reader3(Reader);

	thread Writer1(Writer);
	thread Writer2(Writer);

	Reader1.join();
	Reader2.join();
	Reader3.join();

	Writer1.join();
	Writer2.join();

	system("PAUSE");

	return 0;
}