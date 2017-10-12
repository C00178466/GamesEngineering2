#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Animation.h"

class Sprite
{
public:
	Sprite(SDL_Window*);
	~Sprite();
	void AnimateClimb();
	void AnimateJump();
	void AnimateIdle();
	void Render();
	void CleanUp();

private:
	SDL_Rect playerRect;
	SDL_Rect frameRect;
	SDL_Texture * texture;

	Animation spriteFSM;
	SDL_Renderer* renderer;
};