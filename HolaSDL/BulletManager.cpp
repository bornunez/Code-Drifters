#include "BulletManager.h"
#include "Game.h"
#include "PlayState.h"
#include "ResourceManager.h"
#include "DecelerationComponent.h"
//Inicializacion de instance
BulletManager* BulletManager::instance = nullptr;

BulletManager::BulletManager()
{
}

void BulletManager::createInstance()
{
	if (instance == nullptr)
		instance = new BulletManager();
}

void BulletManager::ResetInstance()
{
	delete instance; // REM : it works even if the pointer is NULL (does nothing then)
	instance = nullptr; // so GetInstance will still work.
}

BulletManager::~BulletManager()
{
	for (Bullet* b : bullets)
		delete b;
}

void BulletManager::handleEvents(SDL_Event & event)
{

}

void BulletManager::update()
{
	for (Bullet* bullet : bullets) {
		if (bullet->isActive()) {
			bullet->update();
			//Si la bala sale de pantalla se desactiva
			if (bullet->getType() != BulletType::BossBullet)
			{
				if (bullet->getDisplayCenterPos().getX() > Game::getGame()->getWinW() || bullet->getDisplayCenterPos().getX() < 0
					|| bullet->getDisplayCenterPos().getY() > Game::getGame()->getWinH() || bullet->getDisplayCenterPos().getY() < 0)
					bullet->setActive(false);
			}
		}
	}
}

void BulletManager::render()
{
	for (Bullet* bullet : bullets) {
		if (bullet->isActive())
			bullet->render();
	}
}

std::vector<Bullet*>& BulletManager::getBullets()
{
	return bullets;
}

Bullet * BulletManager::getBullet(BulletType bulletType)
{
	for (Bullet* bullet : bullets) {
		if (!bullet->isActive() && bullet->getType() == bulletType) {
			bullet->setActive(true);
			return bullet;
		}
	}

	Bullet* newBullet = nullptr;

	if(bulletType == BulletType::MCBullet)
		newBullet = new Bullet(ResourceManager::getInstance()->getTexture(MCBullet), true, bulletType);
	
	else if(bulletType == BulletType::GunnerBullet)
		newBullet = new Bullet(ResourceManager::getInstance()->getTexture(GunnerBullet), true, bulletType);
	else if (bulletType == BulletType::BossBullet)
		newBullet = new Bullet(ResourceManager::getInstance()->getTexture(BossBullet), true, bulletType);

	bullets.push_back(newBullet);
	return newBullet;
}


void BulletManager::shoot(GameObject * owner, Transform bulletTransform, BulletType bulletType)
{
	Bullet* newBullet = getBullet(bulletType);

	newBullet->setTransform(bulletTransform);
	float angle = atan2(bulletTransform.direction.getY(), bulletTransform.direction.getX());
	angle = angle * 180 / M_PI;
	if (angle < 0)
		angle += 360;
	newBullet->setAngle(angle);
	//Se envia el mensaje de que se ha creado una bala, deberia enviarse al sound manager
	//Message msg(BULLET_CREATED);
	//owner->sendMessage(&msg);
	//this->send(&msg);
}

void BulletManager::shoot(GameObject * owner, Vector2D position, Vector2D velocity, BulletType bulletType)
{
	Bullet* newBullet = getBullet(bulletType);
	newBullet->getTransform()->position = position;
	newBullet->getTransform()->velocity = velocity;

	//Se envia el mensaje de que se ha creado una bala, deberia enviarse al sound manager
	Message msg(BULLET_CREATED);
	owner->sendMessage(&msg);
}

void BulletManager::receive(Message * msg)
{
}