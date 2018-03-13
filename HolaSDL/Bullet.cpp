#include "Bullet.h"

Bullet::Bullet(Texture * tex, Transform t, bool active) :GameObject()
{
	texture = tex;
	transform = t;
	
}

Bullet::~Bullet()
{
}
