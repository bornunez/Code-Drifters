#include "TurretShotComponent.h"
#include "GameObject.h"
#include "Bullet.h"
#include "GunnerBulletComponent.h"
#include "GunnerBulletRenderComponent.h"
#include "Game.h"
#include "MainCharacter.h"
#include "PlayState.h"
#include "ResourceManager.h"
#include "EnemyTurret.h"
#include "Camera.h"


TurretShotComponent::TurretShotComponent(GameObject* o, GameObject* target, float dist, float delay)
	: UpdateComponent(o)
{
	et = static_cast<EnemyTurret*>(gameObject);
	targetObject = target;
	distance = dist;
	shotDelay = delay;
	lastShotTimer = new Timer();
}

TurretShotComponent::~TurretShotComponent()
{
}


void TurretShotComponent::handleAnimation()
{
	et = static_cast<EnemyTurret*>(gameObject);

	if ((abs(targetObject->getTransform()->position.getX() - getGameObject()->getTransform()->position.getX()) +
		abs(targetObject->getTransform()->position.getY() - getGameObject()->getTransform()->position.getY())) <= distance) {
		if (et->enemyState == EnemyState::Idle) { 
			et->enemyState = EnemyState::Run;
			Message msg(TURRET_ALERT);
			gameObject->sendMessage(&msg);
		}
	}
	else if (et->enemyState == EnemyState::Attack){
		et->enemyState = EnemyState::Charge;
		Message msg(TURRET_ALERT_OVER);
		gameObject->sendMessage(&msg);
	}
}

void TurretShotComponent::updateGunPosition()
{
	Vector2D aux = et->getCurrentAnimation()->getCurrentFrame()->getGunPosition();
	gunPosition = aux;
}


void TurretShotComponent::shoot() {
	Transform* gunnerT = gameObject->getTransform();
	Transform* targetT = targetObject->getTransform();
	EnemyTurret* et = static_cast<EnemyTurret*>(gameObject);
	if (et->enemyState == EnemyState::Attack){
		if (lastShotTimer->TimeSinceTimerCreation > shotDelay) {
			lastShotTimer->restart();
			updateGunPosition();
			Transform bulletTransform;

			bulletTransform.direction = (targetT->position - gunnerT->position);
			bulletTransform.direction.normalize();
			bulletTransform.body.w = 50;
			bulletTransform.body.h = 15;
			bulletTransform.position.set(gunPosition.getX() - bulletTransform.body.w / 2, gunPosition.getY() - bulletTransform.body.h / 2);
			bulletTransform.velocity = bulletTransform.direction;
			bulletTransform.speed = 1000.0;

			BulletManager::getInstance()->shoot(this->gameObject, bulletTransform, BulletType::GunnerBullet);

		}
	}

}

void TurretShotComponent::update() {
	if (!gameObject->isDead()) {
		lastShotTimer->update();
		if (!static_cast<Enemy*>(gameObject)->isStunned())
			shoot();
		handleAnimation();
	}
}
