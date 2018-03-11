#pragma once
#include "sdl_includes.h"
class Transform;
class TileLayer;


class CollisionHandler
{
public:
	static bool Collide(Transform* A, Transform* B);
	static bool Collide(Transform* A, TileLayer* tileLayer);
	static bool Collide(SDL_Rect A, TileLayer * tileLayer);
	static int RectCollide(SDL_Rect a, SDL_Rect b);
	CollisionHandler();
	virtual ~CollisionHandler();
};

