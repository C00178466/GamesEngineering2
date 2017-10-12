#include "State.h"

void Idle::jumping(Animation* a)
{
	cout << "Jumping" << endl;
	a->setCurrent(new Idle());
	delete this;
}

void Idle::climbing(Animation* a)
{
	cout << "Climbing" << endl;
	a->setCurrent(new Idle());
	delete this;
}