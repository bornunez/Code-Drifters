#include "Particle.h"
#include "SimpleAnimationComponent.h"

Particle::Particle(Texture * texture, ParticleType type, int x, int y)
{
	this->getTransform()->position.setX(x);
	this->getTransform()->position.setY(y);
	this->type = type;
	simpleAnimation = new SimpleAnimationComponent(this, texture, 0, 200, SDL_FLIP_NONE, false);
	this->addComponent(simpleAnimation);
}

Particle::~Particle()
{
}
