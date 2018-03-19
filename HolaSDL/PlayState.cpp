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
	SDL_RenderClear(Game::getGame()->getRenderer());
	LevelManager::getInstance()->render();
	GameState::render();
	EnemyManager::getInstance()->render();
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
	EnemyManager::getInstance()->update();
	//level->getRoom(mainCharacter->getCurrentRoomX(), mainCharacter->getCurrentRoomY())->update();//Hace el update de la sala actual	
	//cout << enemy->getTransform()->position;
}

void PlayState::loadState()
{
	//Creamos el puntero, es todo lo que hace falta
	camera = new Camera();

	//IMPORTANTE: Crear primero la camara. El mapa la requiere
	LevelManager::getInstance()->init();
	

	mainCharacter = new MainCharacter(nullptr,32*3*Game::getGame()->getScale(), 32*3 * Game::getGame()->getScale(), 32 * Game::getGame()->getScale(), 32 * Game::getGame()->getScale());

	camera->load();


	//level->getFirstRoom()->addCharacter(mainCharacter);//Se añade el personaje a la primera sala
	addGameObject(mainCharacter);


	//EnemyManager Requiere de MainCharacter : HACER DESPUES DE MAINCHARACTER
	EnemyManager::getInstance()->init(mainCharacter);

	LevelManager::getInstance()->getFirstRoom()->spawn();


}
