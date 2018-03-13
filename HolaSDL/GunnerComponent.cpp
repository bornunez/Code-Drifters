#pragma once
#include "GunnerComponent.h"
#include "GameObject.h"
#include <cmath>

#include "Bullet.h"
#include "ResourceManager.h"
#include "Game.h"
#include "PlayState.h"
#include "MCBulletComponent.h"
#include "MCBulletRenderComponent.h"
#include "Room.h"
#include "DungeonGenerator.h"
#include "Camera.h"
#include "MainCharacter.h"

GunnerComponent::GunnerComponent(GameObject* o, GameObject* target, float vel, float dist) : UpdateComponent(o)
{
	targetObject = target;
	velocity = vel;
	distancia = dist;

	lastShotTime = new Timer();

}


GunnerComponent::~GunnerComponent()
{
}

void GunnerComponent::shoot(){
	int shotDelay = 3;

	if (lastShotTime->TimeSinceTimerCreation > shotDelay && ! hadisparaoxd) {//Si el tiempo desde la última recarga supera al tiempo de recarga del personaje
		
			lastShotTime->restart();//Reinicia el tiempo desde la última recarga
			int X = gameObject->getTransform()->position.getX();
			int Y = gameObject->getTransform()->position.getY();
			int currentX = dynamic_cast<MainCharacter*>(targetObject)->getCurrentRoomX(); //esto requiere arreglo
			int currentY = dynamic_cast<MainCharacter*>(targetObject)->getCurrentRoomY();

			Transform bulletTransform;
			bulletTransform.position.set(X, Y);
			bulletTransform.direction = (targetObject->getTransform()->position - getGameObject()->getTransform()->position);
			bulletTransform.direction.normalize();
			bulletTransform.body.w = bulletTransform.body.h = 10;
			Bullet* auxBullet = new Bullet(Game::getGame()->getResourceManager()->getTexture(BulletSprite), bulletTransform, true);

			//Le añade los componentes de físicas y render
			auxBullet->addComponent(new MCBulletComponent(auxBullet, 1.5));
			auxBullet->addComponent(new MCBulletRenderComponent(auxBullet));

			//Añade la bala a los objetos de la sala actual
			PlayState::getInstance()->addGameObject(auxBullet);

			hadisparaoxd = true;
	}
	
}

void GunnerComponent::update() {

	lastShotTime->update();
	shoot();
	

	gunnerPosition = getGameObject()->getTransform()->position;
	targetPosition = targetObject->getTransform()->position;
	if ((abs(targetPosition.getX() - gunnerPosition.getX()) + abs(targetPosition.getY() - gunnerPosition.getY()))
		<= distancia) {
		getGameObject()->getTransform()->velocity.set(0.0f, 0.0);
		
		//disparo si tiempo
	}
	//Regular chase
	else {
		if (gunnerPosition.getX() > targetPosition.getX()) {
			getGameObject()->getTransform()->velocity.setX(-velocity);
		}
		else getGameObject()->getTransform()->velocity.setX(velocity);

		if (gunnerPosition.getY() > targetPosition.getY()) {
			getGameObject()->getTransform()->velocity.setY(-velocity);
		}
		else getGameObject()->getTransform()->velocity.setY(velocity);
	}

	//horizontal chase
	/*else {
		if (abs(targetPosition.getX() - gunnerPosition.getX()) >= abs(targetPosition.getY() - gunnerPosition.getY())) {
			getGameObject()->getTransform()->velocity.setY(0.0f);
			if (gunnerPosition.getX() > targetPosition.getX()) {
				getGameObject()->getTransform()->velocity.setX(-velocity);
			}
			else getGameObject()->getTransform()->velocity.setX(velocity);
		
		}
		else  {
			getGameObject()->getTransform()->velocity.setX(0.0f);
			if (gunnerPosition.getY() > targetPosition.getY()) {
				getGameObject()->getTransform()->velocity.setY(-velocity);
			}
			else { getGameObject()->getTransform()->velocity.setY(velocity); }
		
		}
		
	}
	std::cout << getGameObject()->getTransform()->velocity << '\n';*/
	getGameObject()->getTransform()->position.set(gunnerPosition + getGameObject()->getTransform()->velocity);


}
