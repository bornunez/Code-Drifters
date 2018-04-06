#include "GunnerShotComponent.h"
#include "GameObject.h"
#include "Bullet.h"
#include "GunnerBulletComponent.h"
#include "GunnerBulletRenderComponent.h"
#include "Game.h"

#include "MainCharacter.h"
#include "PlayState.h"
#include "ResourceManager.h"
#include "EnemyGunner.h"
#include "Camera.h"


GunnerShotComponent::GunnerShotComponent(GameObject* o, GameObject* target, float dist, float delay) 
	: UpdateComponent(o)
{
	targetObject = target;
	distance = dist;
	shotDelay = delay;

	lastShotTime = new Timer();
	shotAnimationTime = new Timer();
}

GunnerShotComponent::~GunnerShotComponent()
{
}

	
void GunnerShotComponent::handleAnimation()
{
	EnemyGunner* eg = static_cast<EnemyGunner*>(gameObject);

	//CÁLCULO DEL ÁNGULO ENTRE EL TARGET Y EL ENEMIGO
	Vector2D aux;
	aux.setX(getGameObject()->getTransform()->position.getX() + getGameObject()->getTransform()->body.w / 2);
	aux.setY(getGameObject()->getTransform()->position.getY() + getGameObject()->getTransform()->body.h / 2);



	Vector2D displayPosition;//Posición del personaje relativa a la cámara
	displayPosition = aux - (PlayState::getInstance()->getCamera()->getTransform()->position);
	float angle = (atan2(targetObject->getDisplayCenterPos().getY() - displayPosition.getY(), targetObject->getDisplayCenterPos().getX() - displayPosition.getX()));//Angulo entre el enemigo y el target, en grados
	angle = angle * 180 / M_PI;


	if (angle < 0)
		angle += 360;

	if (shotAnimationTime->TimeSinceTimerCreation == 0) {
		if (angle > 297 && angle < 342) {
			if (eg->currentState == SHOOT) {
				Message msg(SHOT_TOPRIGHT);
				gameObject->sendMessage(&msg);
			}
			gameObject->getTransform()->direction.set(1, -1);
		}
		else if (angle > 252 && angle < 297) {
			if (eg->currentState == SHOOT) {
				Message msg(SHOT_TOP);
				gameObject->sendMessage(&msg);
			}
			gameObject->getTransform()->direction.set(0, -1);
		}
		else if (angle > 207 && angle <= 252) {
			if (eg->currentState == SHOOT) {
				Message msg(SHOT_TOPLEFT);
				gameObject->sendMessage(&msg);
			}
			gameObject->getTransform()->direction.set(-1, -1);
		}
		else if (angle > 162 && angle < 207) {
			if (eg->currentState == SHOOT) {
				Message msg(SHOT_LEFT);
				gameObject->sendMessage(&msg);
			}
			gameObject->getTransform()->direction.set(-1, 0);
		}
		else if (angle >= 117 && angle < 162) {
			if (eg->currentState == SHOOT) {
				Message msg(SHOT_BOTLEFT);
				gameObject->sendMessage(&msg);
			}
			gameObject->getTransform()->direction.set(-1, 1);
		}
		else if (angle > 72 && angle < 117) {
			if (eg->currentState == SHOOT) {
				Message msg(SHOT_BOT);
				gameObject->sendMessage(&msg);
			}

			gameObject->getTransform()->direction.set(0, 1);
		}
		else if (angle > 27 && angle < 72) {
			if (eg->currentState == SHOOT) {
				Message msg(SHOT_BOTRIGHT);
				gameObject->sendMessage(&msg);
			}


			gameObject->getTransform()->direction.set(1, 1);
		}
		else {
			if (eg->currentState == SHOOT) {
				Message msg(SHOT_RIGHT);
				gameObject->sendMessage(&msg);
			}
			gameObject->getTransform()->direction.set(1, 0);
		}
	}

	if (eg->currentState == SHOOT) {
		shotAnimationTime->update();

		if (shotAnimationTime->TimeSinceTimerCreation > 0.45) {
			eg->currentState = IDLE;
		}
	}

}

void GunnerShotComponent::updateGunPosition()
{
	EnemyGunner* eg = static_cast<EnemyGunner*>(gameObject);
	Vector2D aux = eg->getCurrentAnimation()->getCurrentFrame()->getGunPosition();
	gunPosition = aux;
}


void GunnerShotComponent::shoot() {
	Transform* gunnerT = gameObject->getTransform();
	Transform* targetT = targetObject->getTransform();
	EnemyGunner* eg = static_cast<EnemyGunner*>(gameObject);
	if (lastShotTime->TimeSinceTimerCreation > shotDelay && 
		(abs(targetT->position.getX() - gunnerT->position.getX()) + abs(targetT->position.getY() - gunnerT->position.getY())) <= distance) {
		if (eg->currentState == IDLE) {
			lastShotTime->restart();
			updateGunPosition();
			Transform bulletT;
			bulletT.position.set(gunPosition.getX(), gunPosition.getY());
			bulletT.direction = (targetT->position - gunnerT->position);
			bulletT.direction.normalize();
			bulletT.body.w = bulletT.body.h = 10;
			Bullet* auxBullet = new Bullet(ResourceManager::getInstance()->getTexture(BulletSprite), bulletT, true);

			//Le añade los componentes de físicas y render
			auxBullet->addComponent(new GunnerBulletComponent(auxBullet));
			auxBullet->addComponent(new GunnerBulletRenderComponent(auxBullet));

			//Añade la bala a los objetos de la sala actual
			PlayState::getInstance()->addGameObject(auxBullet);

			shotAnimationTime->restart();
			eg->currentState = SHOOT;
		}		
	}

}

void GunnerShotComponent::update() {
	lastShotTime->update();
	shoot();
	handleAnimation();
}

