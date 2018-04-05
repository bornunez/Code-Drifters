#include "BulletManager.h"
#include "Message.h"
#include "Game.h"

BulletManager::BulletManager()
{
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

	Bullet* newBullet = new Bullet();
	//newBullet->addPhysicsComponent(&bulletPhysics);
	//newBullet->addRenderComponent(&bulletRenderer);
	bullets.push_back(newBullet);
	return newBullet;
}

void BulletManager::shoot(GameObject * owner, Vector2D position, Vector2D velocity)
{
	Bullet* newBullet = getBullet();
	newBullet->getTransform()->position = position;
	newBullet->getTransform()->velocity = velocity;

	//newBullet->setPosition(position);
	//newBullet->setVelocity(velocity);

	//Se envia el mensaje de que se ha creado una bala, deberia enviarse al sound manager
	Message msg(BULLET_CREATED);
	owner->sendMessage(&msg);
	//this->send(&msg);
}

void BulletManager::receive(Message * msg)
{
	/*switch (msg->id) {
	case ROUND_START:
		for (Bullet* bullet : bullets)
			bullet->setActive(false);
		break;
	case ROUND_OVER:
		for (Bullet* bullet : bullets)
			bullet->setActive(false);
		break;
	case BULLET_ASTROID_COLLISION:
		static_cast<BulletAstroidCollision*>(msg)->bullet_->setActive(false);
		break;
	case BULLET_FIGHTER_COLLISION:
		static_cast<BulletFighterCollision*>(msg)->bullet_->setActive(false);
		break;
	case FIGHTER_SHOOT:
		FighterIsShooting * aux = static_cast<FighterIsShooting*>(msg);
		shoot(aux->fighter_, aux->bulletPosition_, aux->bulletVelocity_);
		break;
	}*/
}