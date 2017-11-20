#include <SDL.h>
#include <SDL_image.h>
#include "ControlComponent.h"
#include "Entity.h"
#include "Component.h"
#include "HealthComponent.h"
#include "PositionComponent.h"
#include "AISystem.h"
#include "ControlSystem.h"
#include "RenderSystem.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window = SDL_CreateWindow("FSM", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	bool running = true;

	//cretae components
	HealthComponent hc;
	PositionComponent pc;
	ControlComponent cc;

	//create Player entity and add components
	Entity player;
	player.addComponent(hc);
	player.addComponent(pc);
	player.addComponent(cc);

	//create Alien entity and add components
	Entity alien;
	alien.addComponent(hc);
	alien.addComponent(pc);

	//create Dog entity and add components
	Entity dog;
	dog.addComponent(hc);
	dog.addComponent(pc);

	//create Cat entity and add components
	Entity cat;
	cat.addComponent(hc);
	cat.addComponent(pc);

	//create the systems
	AISystem ai;
	ControlSystem cs;
	RenderSystem rs;

	//add entities to systems
	ai.AddEntity(player);
	cs.AddEntity(player);
	rs.AddEntity(player);

	while (running)
	{
		ai.Update();
		cs.Update();
		rs.Update();
		SDL_Event e;

		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			}
		}
	}

	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();

	return 0;
}