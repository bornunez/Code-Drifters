#include "Bullet.h"

Bullet::Bullet(PlayState* playState, Texture * tex, Transform t, bool active) : PlayStateObject(playState, tex, t, true)
{
}

Bullet::~Bullet()
{
}
