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

Bullet * BulletManager::getBullet()
{
	for (Bullet* bullet : bullets) {
		if (!bullet->isActive()) {
			bullet->setActive(true);
			return bullet;
		}
	}

	Bullet* newBullet = new Bullet(ResourceManager::getInstance()->getTexture(BulletSprite), true);

	//newBullet->addPhysicsComponent(&bulletPhysics);
	//newBullet->addRenderComponent(&bulletRenderer);
	bullets.push_back(newBullet);
	return newBullet;
}


void BulletManager::shoot(GameObject * owner, Transform bulletTransform)
{
	Bullet* newBullet = getBullet();

	newBullet->setTransform(bulletTransform);

	//Es necesario añadirla si ya ha sido añadida??
	//PlayState::getInstance()->addGameObject(newBullet);

	//Se envia el mensaje de que se ha creado una bala, deberia enviarse al sound manager
	Message msg(BULLET_CREATED);
	owner->sendMessage(&msg);
	//this->send(&msg);
}

void BulletManager::shoot(GameObject * owner, Vector2D position, Vector2D velocity)
{
	Bullet* newBullet = getBullet();
	newBullet->getTransform()->position = position;
	newBullet->getTransform()->velocity = velocity;

	//Se envia el mensaje de que se ha creado una bala, deberia enviarse al sound manager
	Message msg(BULLET_CREATED);
	owner->sendMessage(&msg);
}

void BulletManager::receive(Message * msg)
{
}