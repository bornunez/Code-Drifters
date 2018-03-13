#include "MCBulletComponent.h"
#include "GameObject.h"



MCBulletComponent::MCBulletComponent(GameObject* o, float maxVelocity) : UpdateComponent(o)
{
	velocity.set(maxVelocity,maxVelocity);
}
void MCBulletComponent::update()
{
	Transform* t = gameObject->getTransform();
	t->velocity.setX(velocity.getX()*t->direction.getX());//Asigna la velocidad al personaje
	t->velocity.setY(velocity.getY()*t->direction.getY());
	t->position.set(t->position + t->velocity);
}


MCBulletComponent::~MCBulletComponent()
{
}
