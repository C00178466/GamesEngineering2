#include "Animation.h"
#include "Sprite.h"
#include "State.h"
#include <SDL.h>
#include <SDL_image.h>
#include <chrono>
#include <thread>

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	SDL_Window* window = SDL_CreateWindow("FSM", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	bool running = true;
	Sprite player(window);

	while (running)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				false;
			}

			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;

			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_SPACE)
				{
					player.AnimateJump();
				}

				if (event.key.keysym.sym == SDLK_UP)
				{
					player.AnimateClimb();

				}
			}
		}

		player.Render();
	}

	//clean up
	SDL_DestroyWindow(window);
	player.CleanUp();
	window = nullptr;
	SDL_Quit();

	return 0;
}