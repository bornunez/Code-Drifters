#pragma once
#include "GameObject.h"
#include "MainCharacter.h"
//
class CollisionsManager : public GameObject
{
private:
	MainCharacter * mainCharacter;
	

public:
	CollisionsManager(MainCharacter* mc);
	virtual ~CollisionsManager();
	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
};