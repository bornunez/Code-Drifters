#pragma once
#include "checkML.h"
#include "GameState.h"
class UpperGameState: public GameState
{
private: 
	GameState * inferior;
public:
	UpperGameState(GameState* inf);
	virtual ~UpperGameState();

	virtual void update();
	virtual void render();
	virtual void handleEvent(SDL_Event& e);
};

