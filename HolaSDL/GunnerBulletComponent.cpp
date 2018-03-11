#include "GunnerBulletComponent.h"
#include "GameObject.h"



GunnerBulletComponent::GunnerBulletComponent(GameObject* o) : UpdateComponent(o){}

void GunnerBulletComponent::update()
{
	Transform* bulletT = gameObject->getTransform();
	bulletT->velocity.setX(bulletT->direction.getX());//Asigna la velocidad al personaje
	bulletT->velocity.setY(bulletT->direction.getY());
	bulletT->position.set(bulletT->position + bulletT->velocity);
}


GunnerBulletComponent::~GunnerBulletComponent()
{
}
