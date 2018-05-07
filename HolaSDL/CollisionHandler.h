#pragma once
#include "sdl_includes.h"
#include <vector>
class Transform;
class TileLayer;
class GameObject;

using namespace std;

class CollisionHandler
{
public:
	static bool Collide(Transform* A, Transform* B);
	static bool Collide(GameObject* A, GameObject* B);
	static bool Collide(Transform* A, TileLayer* tileLayer);
	static bool Collide(SDL_Rect A, TileLayer* tileLayer);
	static vector<bool> Collide(std::vector<SDL_Rect> rects, TileLayer* tileLayer);
	static vector<bool> Collide(std::vector<SDL_Rect> rects, SDL_Rect rec);
	static int RectCollide(SDL_Rect a, SDL_Rect b);
	CollisionHandler();
	virtual ~CollisionHandler();
};

