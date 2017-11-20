#pragma once
#include "Entity.h"
#include <iostream>

using namespace std;

class RenderSystem {
public:
	RenderSystem() {}
	~RenderSystem() {}

	void AddEntity(Entity e)
	{
		entities.push_back(e);
	}

	void Update()
	{
		for (int i = 0; i < entities.size(); i++)
		{
			cout << "Render System Updating" << endl;
		}
	}

private:
	vector<Entity> entities;
};