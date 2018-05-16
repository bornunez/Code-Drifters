#pragma once
//#include "checkML.h"
#include "Vector2D.h"
#include "sdl_includes.h"

struct OverlapCollision {
	bool active=true;
	SDL_Rect overlapBody;
	Vector2D overlapOffset;
};
struct Transform
{
	Vector2D position;
	Vector2D rotation;
	Vector2D velocity;
	Vector2D direction;
	SDL_Rect body;
	OverlapCollision overlapCollision;
	float speed;
};
