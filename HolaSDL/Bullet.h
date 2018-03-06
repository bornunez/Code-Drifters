#pragma once
#include "PlayStateObject.h"


class Bullet : public PlayStateObject
{
private:

public:
	Bullet(PlayState* playState, Game* game, Texture* tex, Transform t, bool active);
	~Bullet();

};