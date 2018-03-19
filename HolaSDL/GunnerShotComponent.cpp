#include "GunnerShotComponent.h"
#include "GameObject.h"
#include "Bullet.h"
#include "GunnerBulletComponent.h"
#include "GunnerBulletRenderComponent.h"
#include "Game.h"

#include "MainCharacter.h"
#include "PlayState.h"
#include "Managers.h"



GunnerShotComponent::GunnerShotComponent(GameObject* o, GameObject* target, float vel, float dist) 
	: UpdateComponent(o)
{
	targetObject = target;
	distance = dist;
	velocity = vel;

	lastShotTime = new Timer();

}

GunnerShotComponent::~GunnerShotComponent()
{
}


void GunnerShotComponent::shoot() {
	int shotDelay = 3;

	if (lastShotTime->TimeSinceTimerCreation > shotDelay && !hadisparaoxd) {
		Transform* gunnerT = gameObject->getTransform();
		Transform* targetT = targetObject->getTransform();
		lastShotTime->restart();

		Transform bulletT;
		bulletT.position.set(gunnerT->position.getX(), gunnerT->position.getY());
		bulletT.direction = (targetT->position - gunnerT->position);
		bulletT.direction.normalize();
		bulletT.body.w = bulletT.body.h = 10;
		Bullet* auxBullet = new Bullet (GameManager::getInstance()->getResourceManager()->getTexture(BulletSprite), bulletT, true);

		//Le añade los componentes de físicas y render
		auxBullet->addComponent(new GunnerBulletComponent(auxBullet));
		auxBullet->addComponent(new GunnerBulletRenderComponent(auxBullet));

		//Añade la bala a los objetos de la sala actual
		GameManager::getInstance()->getPlayState()->addGameObject(auxBullet);

		hadisparaoxd = true;
	}

}

void GunnerShotComponent::update() {
	lastShotTime->update();
	shoot();
}

