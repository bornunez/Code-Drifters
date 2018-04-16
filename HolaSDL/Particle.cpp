#include "Particle.h"
#include "SimpleAnimationComponent.h"

Particle::Particle(Texture * texture, int x, int y)
{
	this->getTransform()->position.setX(x);
	this->getTransform()->position.setY(y);
	this->addComponent(new SimpleAnimationComponent(this, texture));
}

Particle::~Particle()
{
}
