#include "Sprite.h"

Sprite::Sprite(SDL_Window* window)
{
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	texture = IMG_LoadTexture(renderer, "spritesheet.png");

	SDL_SetRenderDrawColor(renderer, 168, 230, 255, 255);
	SDL_RenderClear(renderer);

	//dimensions of 1 actual frame
	frameRect.x = frameRect.y = 0;
	frameRect.w = 361;
	frameRect.h = 497;

	//dimensions of the frame to be drawn
	playerRect.x = playerRect.y = 0;
	playerRect.w = 64;
	playerRect.h = 64;
}

Sprite::~Sprite() {}

void Sprite::Render()
{	
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, &frameRect, &playerRect);
	SDL_RenderPresent(renderer);
}

void Sprite::AnimateClimb()
{
	frameRect.y = 0;
	frameRect.x += 361;

	if (frameRect.x >= 3240)
	{
		frameRect.x = 0;
	}

	spriteFSM.climbing();
}

void Sprite::AnimateJump()
{
	frameRect.y = 497;
	frameRect.x += 361;

	if (frameRect.x >= 3240)
	{
		frameRect.x = 0;
	}

	spriteFSM.jumping();
}

void Sprite::AnimateIdle()
{
	frameRect.y = 994;
	frameRect.x += 361;

	if (frameRect.x >= 3240)
	{
		frameRect.x = 0;
	}

	spriteFSM.idle();
}

void Sprite::CleanUp()
{
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
}