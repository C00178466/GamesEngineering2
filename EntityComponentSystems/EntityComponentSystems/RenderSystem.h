#pragma once
#include "Entity.h"
#include <iostream>

using namespace std;

class RenderSystem {
public:
	RenderSystem();
	~RenderSystem();

private:
	vector<Entity> entities;
};