#include "BulletManager.h"
#include "Message.h"
#include "Game.h"
#include "PlayState.h"
#include "ResourceManager.h"

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
	instance = NULL; // so GetInstance will still work.
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
			if (bullet->getDisplayCenterPos().getX() > Game::getGame()->getWinW() || bullet->getDisplayCenterPos().getX() < 0
				|| bullet->getDisplayCenterPos().getY() > Game::getGame()->getWinH() || bullet->getDisplayCenterPos().getY() < 0)
				bullet->setActive(false);
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

	//Bullet* newBullet = new Bullet(ResourceManager::getInstance()->getTexture(bulletType), true, bulletType);


	//Esta linea funcionaria porque tienen el mismo numero en las enums, quiza cambiarlo a enum class
	//Bullet* newBullet = new Bullet(ResourceManager::getInstance()->getTexture(bulletType), true, bulletType);

	Bullet* newBullet = nullptr;

	if(bulletType == BulletType::MCBullet)
		newBullet = new Bullet(ResourceManager::getInstance()->getTexture(MCBullet), true, bulletType);
	
	else if(bulletType == BulletType::GunnerBullet)
		newBullet = new Bullet(ResourceManager::getInstance()->getTexture(GunnerBullet), true, bulletType);

	bullets.push_back(newBullet);
	return newBullet;
}


void BulletManager::shoot(GameObject * owner, Transform bulletTransform, BulletType bulletType)
{
	Bullet* newBullet = getBullet(bulletType);

	newBullet->setTransform(bulletTransform);

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