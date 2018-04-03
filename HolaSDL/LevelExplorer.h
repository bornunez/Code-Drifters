#pragma once
#include "InputComponent.h"
class LevelExplorer :
	public InputComponent
{
public:
	LevelExplorer(GameObject* o);
	virtual ~LevelExplorer();

	void handleEvents(SDL_Event & e);
};

