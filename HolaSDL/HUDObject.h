#pragma once
#include"GameObject.h"
class HUDObject : public GameObject
{
public:
	HUDObject(Texture* text);
	HUDObject();
	virtual ~HUDObject();

	SDL_Rect destRect,
		srcRect;
};

