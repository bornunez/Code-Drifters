#include "IntroState.h"
#include "Game.h"



IntroState::IntroState()
{

}


IntroState::~IntroState()
{
}

void IntroState::render()
{
	SDL_RenderClear(Game::getGame()->getRenderer());
}

void IntroState::update()
{
	game->startDialogue("intro1");
	//game->endIntro();
}
