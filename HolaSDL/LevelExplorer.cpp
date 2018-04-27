#include "LevelExplorer.h"
#include "Managers.h"

LevelExplorer::LevelExplorer(GameObject * o) : InputComponent(o)
{
}

LevelExplorer::~LevelExplorer()
{
}

void LevelExplorer::handleEvents(SDL_Event & e)
{
	if (e.type == SDL_KEYDOWN) {
		if(e.key.keysym.sym == SDLK_DOWN)
			LevelManager::getInstance()->changeRoom(Down);
		else if (e.key.keysym.sym == SDLK_UP)
			LevelManager::getInstance()->changeRoom(Up);
		else if(e.key.keysym.sym == SDLK_LEFT)
			LevelManager::getInstance()->changeRoom(Left);
		else if (e.key.keysym.sym == SDLK_RIGHT)
			LevelManager::getInstance()->changeRoom(Right);
		else if (e.key.keysym.sym == SDLK_p)
			LevelManager::getInstance()->changeRoom(LevelManager::getInstance()->getBossRoom());
	}
}
