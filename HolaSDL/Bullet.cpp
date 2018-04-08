#include "Bullet.h"
#include "SimpleAnimationComponent.h"
#include "MCBulletComponent.h"
#include "BasicMovement.h"

Bullet::Bullet(Texture * tex, bool active) : GameObject(tex, active)
{
	this->addComponent(new SimpleAnimationComponent(this, texture));

	//Esta llevarla a MCBullet
	this->addComponent(new BasicMovement(this, "Paredes"));
	//this->addComponent(new MCBulletComponent(this, 1.5));
}

Bullet::Bullet(Texture * tex, Transform t, bool active) : GameObject(tex, t, active)
{
	this->addComponent(new SimpleAnimationComponent(this, texture));

	//Esta llevarla a MCBullet
	this->addComponent(new MCBulletComponent(this, 1.5));
}

Bullet::Bullet(Texture * tex, int x, int y, int width, int height, bool active)  : GameObject(tex, x, y, width, height, active)
{
	this->addComponent(new SimpleAnimationComponent(this, texture));
}




Bullet::~Bullet()
{
}
