#pragma once
#include "TestState.h"
#include "Camera.h"
#include "Game.h"
#include "MainCharacter.h"
#include"DungeonGenerator.h"
#include "Enemy.h"
#include "Room.h"

TestState::TestState(Game* g) :GameState(g)
{
	loadState();
}


TestState::~TestState()
{
}

void TestState::render()
{
	SDL_RenderClear(this->getGame()->getRenderer());
	camera->render();
}

void TestState::handleEvent(SDL_Event & e)
{
	mainCharacter->handleEvents(e);
}

void TestState::update()
{
	camera->update();
	level->getRoom(mainCharacter->getCurrentRoomX(), mainCharacter->getCurrentRoomY())->update();//Hace el update de la sala actual	
}

void TestState::addRoomObject(GameObject* o)
{
	level->getRoom(mainCharacter->getCurrentRoomX(), mainCharacter->getCurrentRoomY())->addCharacter(o);
}

void TestState::loadState()
{
	camera = new Camera(this->getGame(), this);

	mainCharacter = new MainCharacter(this, getGame(), nullptr, 100, 100, 50, 50);
	camera->load();

	level = new DungeonGenerator(this, 20, 20, 20, 50, 50);
	level->CreateMap();
	//level->getFirstRoom()->addCharacter(mainCharacter);//Se añade el personaje a la primera sala

	mainCharacter->changeCurrentRoom(level->getFirstRoom()->getX(), level->getFirstRoom()->getY());//Se le asigna la posición de la primera sala

	level->getRoom(mainCharacter->getCurrentRoomX(), mainCharacter->getCurrentRoomY())->addCharacter(mainCharacter);
	//Enemy (test)
	enemy = new Enemy(this, this->getGame(), mainCharacter, 50, 50, 20, 20);

	level->getFirstRoom()->addCharacter(enemy);



}
