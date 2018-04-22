#include "Particle.h"
#include "SimpleAnimationComponent.h"

Particle::Particle(Texture * texture, ParticleType type, int x, int y)
{
	this->getTransform()->position.setX(x);
	this->getTransform()->position.setY(y);
	this->type = type;
	this->addComponent(new SimpleAnimationComponent(this, texture, 0 , 100, SDL_FLIP_NONE, false));
}

Particle::~Particle()
{
}
