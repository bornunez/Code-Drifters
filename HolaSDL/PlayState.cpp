#pragma once
#include "PlayState.h"
#include "Camera.h"
#include "Game.h"
#include "MainCharacter.h"
#include "DungeonGenerator.h"
#include "ExampleEnemy.h"
#include "Room.h"

PlayState::PlayState():GameState ()
{
	loadState();
}


PlayState::~PlayState()
{
}

void PlayState::render()
{
	SDL_RenderClear(this->getGame()->getRenderer());
	camera->render();
}

void PlayState::handleEvent(SDL_Event & e)
{
	mainCharacter->handleEvents(e);
}

void PlayState::update()
{
	camera->update();
	level->getRoom(mainCharacter->getCurrentRoomX(), mainCharacter->getCurrentRoomY())->update();//Hace el update de la sala actual	
}

void PlayState::addRoomObject(GameObject* o)
{
	level->getRoom(mainCharacter->getCurrentRoomX(), mainCharacter->getCurrentRoomY())->addCharacter(o);	
}

void PlayState::loadState()
{
	camera = new Camera(this->getGame(), this);

	mainCharacter = new MainCharacter(this, getGame(), nullptr,200, 200, 50, 50);
	camera->load();

	level = new DungeonGenerator(this, 20, 20, 20, 50, 50);
	level->CreateMap();
	//level->getFirstRoom()->addCharacter(mainCharacter);//Se añade el personaje a la primera sala

	mainCharacter->changeCurrentRoom(level->getFirstRoom()->getX(), level->getFirstRoom()->getY());//Se le asigna la posición de la primera sala

	level->getRoom(mainCharacter->getCurrentRoomX(), mainCharacter->getCurrentRoomY())->addCharacter(mainCharacter);
	//Enemy (test)
//	enemy = new ExampleEnemy(this, this->getGame(), mainCharacter, 50, 50, 20, 20);
	
	//level->getFirstRoom()->addCharacter(enemy);



}
