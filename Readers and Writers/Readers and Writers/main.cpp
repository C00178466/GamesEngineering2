#include <iostream>
#include <thread>
#include "Database.h"
#include "Semaphore.h"

using namespace std;

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
		if (nr == 1)
		{
			P(rw); // wait function
			cout << "Reader using File" << endl;
		}
		V(mutexR); // signal function on mutexxce

		//Read from database
		//db.ReadFromDatabase(1);

		P(mutexR); // wait function
		nr = nr - 1; //decrease number of readers

		if (nr == 0)
		{
			V(rw); // signal function
			
			cout << "Reader releasing File" << endl;
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
		cout << "Writer using file" << endl;

		//write to database
		//int tempNum = rand() % 10 + 1;
		//db.WriteToDatabase(tempNum);

		cout << "Writer releasing file" << endl;
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

	thread Writer1(Writer);
	thread Writer2(Writer);

	Reader1.join();
	Reader2.join();

	Writer1.join();
	Writer2.join();

	system("PAUSE");

	return 0;
}