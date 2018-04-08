#pragma once
#include "GameObject.h"


class Bullet : public GameObject
{
private:

public:
	Bullet(Texture * tex, Transform t, bool active);
	Bullet(Texture * tex, int x, int y, int width, int height, bool active);
	Bullet() {};
	~Bullet();

};