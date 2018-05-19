#include "ShopState.h"
#include "Button.h"
#include "Game.h"



ShopState::ShopState(GameState* upper): UpperGameState(upper)
{
	shopBox = new ShopBox();
	gameObjects.push_back(new Shop(this));
	gameObjects.push_back(shopBox);
}


ShopState::~ShopState()
{
}

void ShopState::createButton(SkillTree* skill)
{
	gameObjects.push_back(new Button(skill));
}

void ShopState::handleEvent(SDL_Event & e)
{
	UpperGameState::handleEvent(e);
	if (e.type == SDL_KEYDOWN) {
		if (e.key.keysym.sym == SDLK_ESCAPE) {
			game->quitState();
		}
	}
}


