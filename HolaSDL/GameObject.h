#pragma once
#include "sdl_includes.h"
#include "ComponentContainer.h"
#include "Texture.h"

class GameObject : public ComponentContainer
{
protected:
	Texture * texture = NULL;
public:
	GameObject();
	~GameObject();
	virtual void update();
	virtual void render();
	virtual void handleEvents(SDL_Event& e);
};

