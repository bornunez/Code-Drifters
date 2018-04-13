#include "Bullet.h"
#include "SimpleAnimationComponent.h"
#include "MCBulletComponent.h"
#include "BasicMovement.h"
#include "BulletAnimationComponent.h"
Bullet::Bullet(Texture * tex, bool active, BulletType type) : GameObject(tex, active)
{
	this->type = type;
	if (type == BulletType::GunnerBullet) {
		this->addComponent(new BulletAnimationComponent(this, texture));
	}
	else if (type == BulletType::MCBullet) {
		this->addComponent(new SimpleAnimationComponent(this, texture));
	}

	//Esta llevarla a MCBullet
	this->addComponent(new BasicMovement(this));
	//this->addComponent(new MCBulletComponent(this, 1.5));
}

Bullet::Bullet(Texture * tex, Transform t, bool active, BulletType type) : GameObject(tex, t, active)
{
	this->type = type;
	this->addComponent(new SimpleAnimationComponent(this, texture));

	//Esta llevarla a MCBullet
	//this->addComponent(new MCBulletComponent(this, 1.5));
}

Bullet::Bullet(Texture * tex, int x, int y, int width, int height, bool active, BulletType type)  : GameObject(tex, x, y, width, height, active)
{
	this->type = type;
	this->addComponent(new SimpleAnimationComponent(this, texture));
}




Bullet::~Bullet()
{
}
