#include "Bullet.h"

Bullet::Bullet(PlayState* playState,Game * game, Texture * tex, Transform t, bool active) : PlayStateObject(playState, game, tex, t, true)
{
}

Bullet::~Bullet()
{
}
