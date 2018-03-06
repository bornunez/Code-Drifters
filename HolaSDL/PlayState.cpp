#pragma once
#include "PlayState.h"
#include "Camera.h"
#include "Game.h"
#include "MainCharacter.h"
#include"DungeonGenerator.h"
#include "Enemy.h"
#include "Room.h"

PlayState::PlayState(Game* g):GameState (g)
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
	for (GameObject* o : sceneObjects) {
		o->update();		
	}	
}

void PlayState::addSceneObject(GameObject* o)
{
	sceneObjects.push_back(o);
}

void PlayState::loadState()
{

	mainCharacter = new MainCharacter(this, getGame(), nullptr, 100, 100, 50, 50);

	level = new DungeonGenerator(this, 20, 20, 20, 50, 50);
	level->CreateMap();
	level->getFirstRoom()->addCharacter(mainCharacter);//Se añade el personaje a la primera sala

	mainCharacter->changeCurrentRoom(level->getFirstRoom()->getX(), level->getFirstRoom()->getY());//Se le asigna la posición de la primera sala


	//Enemy (test)
	enemy = new Enemy(this, this->getGame(), mainCharacter, 50, 50, 20, 20);
	
	level->getFirstRoom()->addCharacter(enemy);

	camera = new Camera(this->getGame(), this);

	sceneObjects.push_back(mainCharacter);
	sceneObjects.push_back(camera);
	sceneObjects.push_back(enemy);			//TEMPORAL
}
