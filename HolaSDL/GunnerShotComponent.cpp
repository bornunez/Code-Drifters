#include "GunnerShotComponent.h"
#include "GameObject.h"
#include "Bullet.h"
#include "GunnerBulletComponent.h"
#include "GunnerBulletRenderComponent.h"
#include "Game.h"

#include "MainCharacter.h"
#include "PlayState.h"
#include "ResourceManager.h"



GunnerShotComponent::GunnerShotComponent(GameObject* o, GameObject* target, float dist, float delay) 
	: UpdateComponent(o)
{
	targetObject = target;
	distance = dist;
	shotDelay = delay;

	lastShotTime = new Timer();

}

GunnerShotComponent::~GunnerShotComponent()
{
}


void GunnerShotComponent::shoot() {
	Transform* gunnerT = gameObject->getTransform();
	Transform* targetT = targetObject->getTransform();

	if (lastShotTime->TimeSinceTimerCreation > shotDelay && 
		(abs(targetT->position.getX() - gunnerT->position.getX()) + abs(targetT->position.getY() - gunnerT->position.getY())) <= distance) {
		
		lastShotTime->restart();

		int currentX = dynamic_cast<MainCharacter*>(targetObject)->getCurrentRoomX(); //esto requiere arreglo
		int currentY = dynamic_cast<MainCharacter*>(targetObject)->getCurrentRoomY();



		Transform bulletT;
		bulletT.position.set(gunnerT->position.getX(), gunnerT->position.getY());
		bulletT.direction = (targetT->position - gunnerT->position);
		bulletT.direction.normalize();
		bulletT.body.w = bulletT.body.h = 10;
		Bullet* auxBullet = new Bullet (Game::getGame()->getResourceManager()->getTexture(BulletSprite), bulletT, true);

		//Le añade los componentes de físicas y render
		auxBullet->addComponent(new GunnerBulletComponent(auxBullet));
		auxBullet->addComponent(new GunnerBulletRenderComponent(auxBullet));

		//Añade la bala a los objetos de la sala actual
		PlayState::getInstance()->addGameObject(auxBullet);
	}

}

void GunnerShotComponent::update() {
	lastShotTime->update();
	shoot();
}

