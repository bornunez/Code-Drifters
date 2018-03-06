#include "MCBulletComponent.h"
#include "GameObject.h"



MCBulletComponent::MCBulletComponent(GameObject* o, float maxVelocity)
{
	gameObject = o;
	type = UpdateC;
	velocity.set(maxVelocity, maxVelocity);
	direction.set(gameObject->getTransform()->direction.getX(), gameObject->getTransform()->direction.getY());
}
void MCBulletComponent::update()
{
	
	getGameObject()->getTransform()->velocity.setX(velocity.getX()*direction.getX());//Asigna la velocidad al personaje
	getGameObject()->getTransform()->velocity.setY(velocity.getY()*direction.getY());
	getGameObject()->getTransform()->position.set(getGameObject()->getTransform()->position + getGameObject()->getTransform()->velocity);
}


MCBulletComponent::~MCBulletComponent()
{
}
