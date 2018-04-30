#include "BomberShotComponent.h"
#include "GameObject.h"
#include "Bullet.h"
#include "GunnerBulletComponent.h"
#include "GunnerBulletRenderComponent.h"
#include "Game.h"

#include "MainCharacter.h"
#include "PlayState.h"
#include "ResourceManager.h"
#include "EnemyBomber.h"
#include "Camera.h"

#include "EnemyBomb.h"
#include "EnemyManager.h"


BomberShotComponent::BomberShotComponent(GameObject* o, GameObject* target, float dist, float delay)
	: UpdateComponent(o)
{
	targetObject = target;
	distance = dist;
	shotDelay = delay;

	lastShotTime = new Timer();
	shotAnimationTime = new Timer();
}

BomberShotComponent::~BomberShotComponent()
{
}

	
void BomberShotComponent::handleAnimation()
{
	EnemyBomber* eb = static_cast<EnemyBomber*>(gameObject);
	float angle = (atan2(targetObject->getCenterPos().getY() - gunPosition.getY(), targetObject->getCenterPos().getX() - gunPosition.getX()));//Angulo entre el enemigo y el target, en grados
	angle = angle * 180 / M_PI;


	if (angle < 0)
		angle += 360;

	if (shotAnimationTime->TimeSinceTimerCreation == 0) {
		
		 if (angle > 90 && angle < 270) {
			if (eb->enemyState == EnemyState::Shoot) {
				Message msg(SHOT_LEFT);
				gameObject->sendMessage(&msg);
			}
		}
		else if (angle > 27 && angle < 72) {
			if (eb->enemyState == EnemyState::Shoot) {
				Message msg(SHOT_RIGHT);
				gameObject->sendMessage(&msg);
			}
		}
	}

	if (eb->enemyState == EnemyState::Shoot) {
		shotAnimationTime->update();

		if (shotAnimationTime->TimeSinceTimerCreation > 0.45) {
			
			eb->enemyState = EnemyState::Run;
		}
	}

}



void BomberShotComponent::shoot() {
	Transform* bomberT = gameObject->getTransform();
	Transform* targetT = targetObject->getTransform();
	EnemyBomber* eb = static_cast<EnemyBomber*>(gameObject);
	if (lastShotTime->TimeSinceTimerCreation > shotDelay && 
		(abs(targetT->position.getX() - bomberT->position.getX()) + abs(targetT->position.getY() - bomberT->position.getY())) <= distance) {
		if (eb->enemyState == EnemyState::Idle) {
			lastShotTime->restart();
			
			
			EnemyManager::getInstance()->spawn(gameObject->getCenterPos().getX(), gameObject->getCenterPos().getY(), Bomb);
	

			shotAnimationTime->restart();
			eb->enemyState = EnemyState::Shoot;
		}		
	}

}

void BomberShotComponent::update() {
	if (!gameObject->isDead()) {
		if (!static_cast<Enemy*>(gameObject)->isStunned()) {
			lastShotTime->update();
			shoot();
		}
		handleAnimation();
	}
}

