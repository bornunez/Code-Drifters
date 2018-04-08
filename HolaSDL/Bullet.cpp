#include "Bullet.h"

Bullet::Bullet(Texture * tex, Transform t, bool active)
{
	texture = tex;
	transform = t;
}

Bullet::Bullet(Texture * tex, int x, int y, int width, int height, bool active)  : GameObject(tex, x, y, width, height, active)
{

}

Bullet::~Bullet()
{
}
