#pragma once

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