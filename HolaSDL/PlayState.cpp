#pragma once
#include "PlayState.h"
#include "Camera.h"
#include "Game.h"
#include "MainCharacter.h"
#include"DungeonGenerator.h"

PlayState::PlayState(Game* g):GameState (g)
{
}


PlayState::~PlayState()
{
}

void PlayState::render()
{
	camera->render();//" "
}

void PlayState::handleEvent(SDL_Event & e)
{
}

void PlayState::update()
{
	camera->update();
	mainCharacter->update();//Provisional en lugar del update
}

void PlayState::loadState()
{
	dungeonGenerator = new DungeonGenerator(this, 20, 20, 20, 50, 50);
	camera = new Camera(this->getGame(), this);
	//Enemy (test)
	mainCharacter = new MainCharacter(getGame(), 100, 100, 50, 50);

	enemy = new Enemy(this, mainCharacter, 50, 50, 20, 20);


}
