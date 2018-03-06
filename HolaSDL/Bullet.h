#pragma once
#include "GameObject.h"


class Bullet : public GameObject
{
private:

public:
	Bullet(Game* game, Texture* tex, Transform t, bool active) : GameObject(game, tex, t, active) {};


};