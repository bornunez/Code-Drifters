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


BomberShotComponent::BomberShotComponent(Enemy* e, GameObject* target, float dist, float delay)
	: UpdateComponent(e)
{
	eb = e;
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

	float angle = (atan2(targetObject->getCenterPos().getY() - gameObject->getCenterPos().getY() , targetObject->getCenterPos().getX() - gameObject->getCenterPos().getX()));//Angulo entre el enemigo y el target, en grados
	angle = angle * 180 / M_PI;


	if (angle < 0)
		angle += 360;

	if (shotAnimationTime->TimeSinceTimerCreation == 0) {
		if (eb->enemyState == EnemyState::Shoot) {
			if (angle > 90 && angle < 270) {
				Message msg(SHOT_LEFT);
				gameObject->sendMessage(&msg);
			}
			else {
				Message msg(SHOT_RIGHT);
				gameObject->sendMessage(&msg);
			}
		}
	}
	if (eb->enemyState == EnemyState::Shoot) {
		shotAnimationTime->update();

		if (shotAnimationTime->TimeSinceTimerCreation > 1) {
			EnemyManager::getInstance()->spawn(gameObject->getCenterPos().getX(), gameObject->getCenterPos().getY(), Bomb);
			eb->enemyState = EnemyState::Run;

		}
	}

}



void BomberShotComponent::shoot() {
	Transform* bomberT = gameObject->getTransform();
	Transform* targetT = targetObject->getTransform();
	if (lastShotTime->TimeSinceTimerCreation > shotDelay && 
		(abs(targetT->position.getX() - bomberT->position.getX()) + abs(targetT->position.getY() - bomberT->position.getY())) <= distance) {
			lastShotTime->restart();

			shotAnimationTime->restart();
			eb->setMovable(false);
			eb->enemyState = EnemyState::Shoot;
			
	}

}

void BomberShotComponent::update() {
	if (!gameObject->isDead()) {
		if (!eb->isStunned()) {
			lastShotTime->update();
			shoot();
		}
		handleAnimation();
	}
}

