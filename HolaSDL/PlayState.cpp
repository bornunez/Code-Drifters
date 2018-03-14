#pragma once
#include "PlayState.h"
#include "GameState.h"
#include "Camera.h"
#include "Game.h"
#include "MainCharacter.h"
#include "DungeonGenerator.h"
#include "ExampleEnemy.h"
#include "Room.h"

PlayState* PlayState::instance = nullptr;

PlayState::PlayState():GameState ()
{
}


PlayState * PlayState::getInstance()
{
	if (instance == nullptr)
		instance = new PlayState();
	return instance;
}

PlayState::~PlayState()
{
}

void PlayState::render()
{
	SDL_RenderClear(this->getGame()->getRenderer());
	camera->render();
	GameState::render();
}

void PlayState::handleEvent(SDL_Event & e)
{
	GameState::handleEvent(e);
	//mainCharacter->handleEvents(e);
}

void PlayState::update()
{
	GameState::update();
	camera->update();
	//level->getRoom(mainCharacter->getCurrentRoomX(), mainCharacter->getCurrentRoomY())->update();//Hace el update de la sala actual	
}


Room* PlayState::getCurrentRoom()
{
	int currRoomX =this->mainCharacter->getCurrentRoomX(); int currRoomY = this->mainCharacter->getCurrentRoomY();
	return this->getLevel()->getRoom(currRoomX, currRoomY);
}

void PlayState::loadState()
{
	camera = new Camera();

	mainCharacter = new MainCharacter(nullptr,32*3*Game::getGame()->getScale(), 32*3 * Game::getGame()->getScale(), 50, 50);
	camera->load();

	level = new DungeonGenerator(this, 20, 20, 20, 50, 50);
	level->CreateMap();
	//level->getFirstRoom()->addCharacter(mainCharacter);//Se añade el personaje a la primera sala

	mainCharacter->changeCurrentRoom(level->getFirstRoom()->getX(), level->getFirstRoom()->getY());//Se le asigna la posición de la primera sala

	addGameObject(mainCharacter);
	//Enemy (test)
//	enemy = new ExampleEnemy(this, this->getGame(), mainCharacter, 50, 50, 20, 20);
	
	//level->getFirstRoom()->addCharacter(enemy);



}
