#pragma once

class Animation
{
	class State* current;

	//Sprite* player;

public:
	Animation();
	
	void setCurrent(State * s) { current = s; }
	void idle();
	void jumping();
	void climbing();
};