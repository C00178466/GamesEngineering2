#pragma once
#include "Entity.h"
#include "ControlComponent.h"
#include <iostream>

using namespace std;

class ControlSystem {
public:
	ControlSystem() {}
	~ControlSystem() {}

	void AddEntity(Entity e)
	{
		entities.push_back(e);
	}

	void Update()
	{
		for (int i = 0; i < entities.size(); i++)
		{
			cout << "Control System Updating" << endl;
		}
	}

private:
	vector<Entity> entities;
};
