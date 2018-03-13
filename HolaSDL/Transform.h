#pragma once
#include "Vector2D.h"
#include "sdl_includes.h"
struct Transform
{
	Vector2D position;
	Vector2D rotation;
	Vector2D velocity;
	Vector2D direction;
	SDL_Rect body;
	double speed;
};
