#include "UpperGameState.h"



UpperGameState::UpperGameState(GameState* inf): inferior(inf)
{
}


UpperGameState::~UpperGameState()
{
}

void UpperGameState::update()
{
	GameState::update();
}

void UpperGameState::render()
{
	inferior->render();
	GameState::render();
}

void UpperGameState::handleEvent(SDL_Event & e)
{
	GameState::handleEvent(e);
}
