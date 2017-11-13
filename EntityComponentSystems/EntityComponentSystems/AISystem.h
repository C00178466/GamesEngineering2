#pragma once
#include "Entity.h"
#include <iostream>

using namespace std;

class AISystem {
public:
	AISystem();
	~AISystem();

	void AddEntity(Entity e);
	void Update();

private:
	vector<Entity> entities;
};