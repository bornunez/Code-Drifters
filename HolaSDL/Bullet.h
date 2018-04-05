#pragma once
#include "GameObject.h"


class Bullet : public GameObject
{
private:

public:
	//Bullet(Texture* tex, Transform t, bool active);
	Bullet(Texture * tex, Transform t, bool active);
	Bullet() {};
	~Bullet();

};