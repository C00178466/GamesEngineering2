#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>

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
};

void P(Semaphore& sem)
{
	sem.m_count--;
}

void V(Semaphore& sem)
{
	sem.m_count++;
}

struct Database
{
public:
	Database()
	{
		//init values of data to 0
		for (int i = 0; i < 10; i++)
		{
			data[i] = 0;
		}
		index = 0;
	}

	~Database() {}

	int ReadFromDatabase(int pos)
	{
		//return element at pos
		return data[pos];
	}

	void WriteToDatabase(int num)
	{
		data[index] = num;
		index++;
	}

private:
	int data[10];
	int index;
};

//number of active readers
int nr = 0;

//Create Database
Database db;

//Create Semaphores
//lock for access to database
Semaphore rw(1);

//lock for reader access to nr
Semaphore mutexR(1);

void Reader()
{
	while (true)
	{
		P(mutexR); // wait function on mutex
		nr = nr + 1; //increase number of readers

		//Check if reader is the first one
		if (nr >= 1)
		{
			P(rw); // wait function

			cout << "Reader: " <<  this_thread::get_id() << " using File" << endl;
		}
		V(mutexR); // signal function on mutex

		//Read from database
		//db.ReadFromDatabase(1);

		P(mutexR); // wait function
		nr--; //decrease number of readers

		if (nr == 0)
		{
			V(rw);

			cout << "Reader: " << this_thread::get_id() << " releasing File" << endl;
		}
		V(mutexR); // signal function on mutex

		this_thread::sleep_for(chrono::seconds(1));
	}
}

void Writer()
{
	while (true)
	{
		P(rw); // wait function on mutex
		cout << "Writer: " << this_thread::get_id() << " using file" << endl;

		//write to database
		//int tempNum = rand() % 10 + 1;
		//db.WriteToDatabase(tempNum);

		cout << "Writer: " << this_thread::get_id() << " releasing file" << endl;
		V(rw); // signal function on mutex

		this_thread::sleep_for(chrono::seconds(1));
	}
}



int main()
{
	srand(NULL);

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