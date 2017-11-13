#pragma once
#include "Entity.h"
#include <iostream>

using namespace std;

class ControlSystem {
public:
	ControlSystem();
	~ControlSystem();

private:
	vector<Entity> entities;
};
