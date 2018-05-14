#pragma once
#include "GameObject.h"

enum class ParticleType { Blood , GunnerBulletExplosion, Stun};
class ParticleAnimation;
class Particle : public GameObject
{
private:
	ParticleType type;
public:
	Particle(Texture* texture, ParticleType type, int x, int y, bool loop=false, double time=0);
	virtual ~Particle();
	ParticleType getType() { return type; }
	ParticleAnimation* particleAnimation;
};

