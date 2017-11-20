#pragma once
#include "Entity.h"
#include <iostream>

using namespace std;

class AISystem {
public:
	AISystem() {}
	~AISystem() {}

	void AddEntity(Entity e)
	{
		entities.push_back(e);
	}

	void Update()
	{
		cout << "AI System Updating" << endl;
	}

private:
	vector<Entity> entities;
};