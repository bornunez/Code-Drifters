#include "MCBulletComponent.h"
#include "GameObject.h"



MCBulletComponent::MCBulletComponent(GameObject* o, float maxVelocity) : UpdateComponent(o)
{
	velocity.set(maxVelocity,maxVelocity);
}
void MCBulletComponent::update()
{
	
	getGameObject()->getTransform()->velocity.setX(velocity.getX()*getGameObject()->getTransform()->direction.getX());//Asigna la velocidad al personaje
	getGameObject()->getTransform()->velocity.setY(velocity.getY()*getGameObject()->getTransform()->direction.getY());
	getGameObject()->getTransform()->position.set(getGameObject()->getTransform()->position + getGameObject()->getTransform()->velocity);
}


MCBulletComponent::~MCBulletComponent()
{
}
