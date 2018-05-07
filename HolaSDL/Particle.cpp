#include "Particle.h"
#include "ParticleAnimation.h"

Particle::Particle(Texture * texture, ParticleType type, int x, int y, bool loop, double time)
{
	this->getTransform()->position.setX(x);
	this->getTransform()->position.setY(y);
	this->type = type;
	particleAnimation = new ParticleAnimation(this, texture, 0, 200, SDL_FLIP_NONE, loop, time);
	this->addComponent(particleAnimation);
}

Particle::~Particle()
{
}
