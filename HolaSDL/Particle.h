#pragma once
#include "GameObject.h"

enum class ParticleType { Blood };

class Particle : public GameObject
{
private:
	ParticleType type;
public:
	Particle(Texture* texture, ParticleType type, int x, int y);
	~Particle();
	ParticleType getType() { return type; }
};

