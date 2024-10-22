#include "LevelExplorer.h"
#include "Managers.h"
#include "Game.h"

LevelExplorer::LevelExplorer(GameObject * o) : InputComponent(o)
{
}

LevelExplorer::~LevelExplorer()
{
}

void LevelExplorer::handleEvents(SDL_Event & e)
{
	if (Game::getGame()->getCheats()) {
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_DOWN)
				LevelManager::getInstance()->changeRoom(Down);
			else if (e.key.keysym.sym == SDLK_UP)
				LevelManager::getInstance()->changeRoom(Up);
			else if (e.key.keysym.sym == SDLK_LEFT)
				LevelManager::getInstance()->changeRoom(Left);
			else if (e.key.keysym.sym == SDLK_RIGHT)
				LevelManager::getInstance()->changeRoom(Right);
			else if (e.key.keysym.sym == SDLK_p)
				LevelManager::getInstance()->changeRoom(LevelManager::getInstance()->getBossRoom());
			else if (e.key.keysym.sym == SDLK_o)
				LevelManager::getInstance()->changeRoom(LevelManager::getInstance()->getShopRoom());
			else if (e.key.keysym.sym == SDLK_8)
				PlayState::getInstance()->nextLevel();
			else if (e.key.keysym.sym == SDLK_z)
				PlayState::getInstance()->getMainCharacter()->changeMoney(1000);

		}
	}
}