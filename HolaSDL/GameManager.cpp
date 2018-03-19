#include "GameManager.h"
#include "Managers.h"
#include "Game.h"
#include "PlayState.h"
#include "Room.h"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager()
{
	resourceManager = new ResourceManager(Game::getGame()->getRenderer());
	enemyManager = new EnemyManager();
	mapManager = new MapManager();
}


GameManager::~GameManager()
{
}

GameManager * GameManager::getInstance()
{
	if (instance == nullptr)
		instance = new GameManager();
	return instance;

}

Camera * GameManager::getCamera()
{
	return playState->getCamera();
}

Room * GameManager::getCurrentRoom()
{
	return mapManager->getCurrentRoom();
}

void GameManager::init()
{
}
