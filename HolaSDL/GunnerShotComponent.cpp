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


GunnerShotComponent::GunnerShotComponent(Enemy* o, GameObject* target, float dist, float delay) 
	: UpdateComponent(o)
{
	eg = o;
	targetObject = target;
	distance = dist;
	shotDelay = delay;

	lastShotTime = new Timer();
	shotAnimationTime = new Timer();
}

GunnerShotComponent::~GunnerShotComponent()
{
	delete lastShotTime;
	delete shotAnimationTime;
}

void GunnerShotComponent::receiveMessage(Message * msg)
{
	switch (msg->id) {
	case ENEMY_SPAWN:;
		lastShotTime->restart();
		shotAnimationTime->restart();
		break;
	}
}
	
void GunnerShotComponent::handleAnimation()
{
	float angle = (atan2(targetObject->getCenterPos().getY() - gunPosition.getY(), targetObject->getCenterPos().getX() - gunPosition.getX()));//Angulo entre el enemigo y el target, en grados
	angle = angle * 180 / M_PI;


	if (angle < 0)
		angle += 360;

	if (shotAnimationTime->TimeSinceTimerCreation == 0) {
		if (angle > 297 && angle < 342) {
			if (eg->enemyState == EnemyState::Shoot) {
				Message msg(SHOT_TOPRIGHT);
				gameObject->sendMessage(&msg);
			}
			gameObject->getTransform()->direction.set(1, -1);
		}
		else if (angle > 252 && angle < 297) {
			if (eg->enemyState == EnemyState::Shoot) {
				Message msg(SHOT_TOP);
				gameObject->sendMessage(&msg);
			}
			gameObject->getTransform()->direction.set(0, -1);
		}
		else if (angle > 207 && angle <= 252) {
			if (eg->enemyState == EnemyState::Shoot) {
				Message msg(SHOT_TOPLEFT);
				gameObject->sendMessage(&msg);
			}
			gameObject->getTransform()->direction.set(-1, -1);
		}
		else if (angle > 162 && angle < 207) {
			if (eg->enemyState == EnemyState::Shoot) {
				Message msg(SHOT_LEFT);
				gameObject->sendMessage(&msg);
			}
			gameObject->getTransform()->direction.set(-1, 0);
		}
		else if (angle >= 117 && angle < 162) {
			if (eg->enemyState == EnemyState::Shoot) {
				Message msg(SHOT_BOTLEFT);
				gameObject->sendMessage(&msg);
			}
			gameObject->getTransform()->direction.set(-1, 1);
		}
		else if (angle > 72 && angle < 117) {
			if (eg->enemyState == EnemyState::Shoot) {
				Message msg(SHOT_BOT);
				gameObject->sendMessage(&msg);
			}

			gameObject->getTransform()->direction.set(0, 1);
		}
		else if (angle > 27 && angle < 72) {
			if (eg->enemyState == EnemyState::Shoot) {
				Message msg(SHOT_BOTRIGHT);
				gameObject->sendMessage(&msg);
			}


			gameObject->getTransform()->direction.set(1, 1);
		}
		else {
			if (eg->enemyState == EnemyState::Shoot) {
				Message msg(SHOT_RIGHT);
				gameObject->sendMessage(&msg);
			}
			gameObject->getTransform()->direction.set(1, 0);
		}
	}

	if (eg->enemyState == EnemyState::Shoot) {
		shotAnimationTime->update();

		if (shotAnimationTime->TimeSinceTimerCreation > 0.45) {
			
			eg->enemyState = EnemyState::Idle;
		}
	}

}

void GunnerShotComponent::updateGunPosition()
{
	Vector2D aux = eg->getCurrentAnimation()->getCurrentFrame()->getGunPosition();
	gunPosition = aux;
}


void GunnerShotComponent::shoot() {
	Transform* gunnerT = gameObject->getTransform();
	Transform* targetT = targetObject->getTransform();
	if (lastShotTime->TimeSinceTimerCreation > shotDelay && 
		(abs(targetT->position.getX() - gunnerT->position.getX()) + abs(targetT->position.getY() - gunnerT->position.getY())) <= distance) {
		if (eg->enemyState == EnemyState::Idle) {
			lastShotTime->restart();
			updateGunPosition();
			Transform bulletTransform;
			bulletTransform.body.w = 20* Game::getGame()->getScale();
			bulletTransform.body.h = 4*Game::getGame()->getScale();			
			bulletTransform.direction = (targetObject->getCenterPos() - gunPosition);
			bulletTransform.direction.setX(targetObject->getCenterPos().getX() - gunPosition.getX() - 25);
			bulletTransform.direction.setY(targetObject->getCenterPos().getY() - gunPosition.getY() - 7);
			bulletTransform.direction.normalize();
			bulletTransform.position.set(gunPosition.getX()- bulletTransform.body.w/2, gunPosition.getY() - bulletTransform.body.h/2);
			bulletTransform.velocity = bulletTransform.direction;
			bulletTransform.speed = 1000.0;

			BulletManager::getInstance()->shoot(this->gameObject, bulletTransform, BulletType::GunnerBullet);
			ResourceManager::getInstance()->getSoundEffect(GunnerShot)->play();

		//	Bullet* auxBullet = new Bullet(ResourceManager::getInstance()->getTexture(BulletSprite), bulletTransform, true);

			//Le añade los componentes de físicas y render
			//auxBullet->addComponent(new GunnerBulletComponent(auxBullet));
			//auxBullet->addComponent(new GunnerBulletRenderComponent(auxBullet));

			//Añade la bala a los objetos de la sala actual
			//PlayState::getInstance()->addGameObject(auxBullet);

			shotAnimationTime->restart();
			eg->enemyState = EnemyState::Shoot;
		}		
	}

}

void GunnerShotComponent::update() {
	if (!gameObject->isDead()) {
		if (!eg->isStunned()){
			shoot();
			lastShotTime->update();
		}
		handleAnimation();
	}
}

