#pragma once
#include "GameObject.h"
class Particle : public GameObject
{
public:
	Particle(Texture* texture, int x, int y);
	~Particle();
};

