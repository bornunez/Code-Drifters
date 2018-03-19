#pragma once
#include "PlayState.h"
#include "GameState.h"
#include "Camera.h"
#include "Game.h"
#include "MainCharacter.h"
#include "DungeonGenerator.h"
#include "ExampleEnemy.h"
#include "Room.h"
#include "Managers.h"

PlayState::PlayState():GameState ()
{
	gameManager = GameManager::getInstance();
	gameManager->setPlayState(this);
	game = Game::getGame();
}

PlayState::~PlayState()
{
}

void PlayState::render()
{
	SDL_RenderClear(this->getGame()->getRenderer());
	camera->render();
	gameManager->getMapManager()->render();
	GameState::render();
	gameManager->getEnemyManager()->render();
}

void PlayState::handleEvent(SDL_Event & e)
{
	GameState::handleEvent(e);
	//mainCharacter->handleEvents(e);
}

void PlayState::update()
{
	GameState::update();
	gameManager->getEnemyManager()->update();
	camera->update();
	//level->getRoom(mainCharacter->getCurrentRoomX(), mainCharacter->getCurrentRoomY())->update();//Hace el update de la sala actual	
	//cout << enemy->getTransform()->position;
}



void PlayState::loadState()
{
	

	mainCharacter = new MainCharacter(nullptr,32*3*game->getScale(), 32*3 * game->getScale(), 32 * game->getScale(), 32 * game->getScale());

	gameManager->getEnemyManager()->init(mainCharacter);
	gameManager->setMainCharacter(mainCharacter);

	camera = new Camera();
	camera->load();

	gameManager->getMapManager()->init();
	/*
	level = new DungeonGenerator(this, 20, 20, 20, 50, 50);
	level->CreateMap();*/
	//level->getFirstRoom()->addCharacter(mainCharacter);//Se añade el personaje a la primera sala

	//mainCharacter->changeCurrentRoom(level->getFirstRoom()->getX(), level->getFirstRoom()->getY());//Se le asigna la posición de la primera sala


	addGameObject(mainCharacter);
	gameManager->getMapManager()->getFirstRoom()->spawn();


}
