#pragma once
#include "PlayStateObject.h"


class Bullet : public PlayStateObject
{
private:

public:
	Bullet(PlayState* playState, Texture* tex, Transform t, bool active);
	~Bullet();

};