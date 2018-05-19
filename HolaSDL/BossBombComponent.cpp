#include "BossBombComponent.h"
#include "GameObject.h"
#include "Bullet.h"
#include "GunnerBulletComponent.h"
#include "GunnerBulletRenderComponent.h"
#include "Game.h"
#include "PlayState.h"
#include "ResourceManager.h"
#include "EnemyBomb.h"
#include "Camera.h"


BossBombComponent::BossBombComponent(Enemy* e, int bulletsNumber, float time, float speed)
	: UpdateComponent(e)
{
	eb = e;
	nBullets = bulletsNumber;
	explodeTime = time;
	bombTimer = new Timer();
	bombSpeed = speed;
}

BossBombComponent::~BossBombComponent()
{
	delete bombTimer;
}

void BossBombComponent::receiveMessage(Message * msg)
{
	switch(msg->id) {
		case ENEMY_SPAWN:
			bombTimer->restart();
		
	}
}


void BossBombComponent::explode() {
	if (bombTimer->TimeSinceTimerCreation > explodeTime) {
		bombTimer->restart();
		Transform bulletTransform;
		bulletTransform.body.w = 50;
		bulletTransform.body.h = 20;
		bulletTransform.position.set(gameObject->getCenterPos().getX() - bulletTransform.body.w / 2, gameObject->getCenterPos().getY() - bulletTransform.body.h / 2);
		
		for (int i = 0; i < nBullets; i++) {
			Vector2D auxVel(0, 1);
			auxVel.rotate((360/nBullets) * (i - 1));
			auxVel.normalize();
			bulletTransform.velocity = bulletTransform.direction = auxVel;
			bulletTransform.speed = bombSpeed;

			BulletManager::getInstance()->shoot(this->gameObject, bulletTransform, BulletType::BossBullet);
		}
		eb->death();
	}

}

void BossBombComponent::update() {
	if (!gameObject->isDead()) {
		bombTimer->update();
		explode();
	}
}