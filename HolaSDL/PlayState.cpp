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
#include "Minimap.h"
#include "CollisionsManager.h"
#include "ItemManager.h"
#include "Boss.h"

#include"HUDManager.h"

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
	/*delete minimap;
	delete mainCharacter;
	delete level;
	delete currentRoom;*/
}

void PlayState::render()
{
	SDL_RenderClear(Game::getGame()->getRenderer());
	LevelManager::getInstance()->render();
	EnemyManager::getInstance()->render();
	GameState::render();
	minimap->render();
	BulletManager::getInstance()->render();
	ItemManager::getInstance()->render();
	HUDManager::getInstance()->render();
}

void PlayState::handleEvent(SDL_Event & e)
{
	if (e.type == SDL_KEYDOWN)//Provisional para debug de dialogos
	{
		if (e.key.keysym.sym == SDLK_l)
		{
			game->startDialogue("1");
		}
	}
	GameState::handleEvent(e);
	//mainCharacter->handleEvents(e);
}

void PlayState::update()
{
	GameState::update();
	camera->update();
	EnemyManager::getInstance()->update();
	BulletManager::getInstance()->update();
	CollisionsManager::getInstance()->update();
	//level->getRoom(mainCharacter->getCurrentRoomX(), mainCharacter->getCurrentRoomY())->update();//Hace el update de la sala actual	
	//cout << enemy->getTransform()->position;
	//HUDManager::getInstance()->update(); //de momento peta
	HUDManager::getInstance()->changeLife(-1);
	//HUDManager::getInstance()->setNewHP(1);
}

void PlayState::endState()
{
	/*camera = nullptr;
	mainCharacter = nullptr;
	EnemyManager::getInstance()->killAll();
	destroyAllGameObjects();*/
}

void PlayState::ResetInstance()
{
	instance->destroyAllGameObjects();
	delete instance; // REM : it works even if the pointer is NULL (does nothing then)
	instance = NULL; // so GetInstance will still work.
}

void PlayState::loadState()
{
	//Creamos el puntero, es todo lo que hace falta
	camera = new Camera();

	//IMPORTANTE: Crear primero la camara. El mapa la requiere
	LevelManager::getInstance()->init();
	int mMapW = Game::getGame()->getWinW() / 5;
	int mMapH = Game::getGame()->getWinW() / 5;
	minimap = new Minimap(mMapW, mMapH, mMapW / 5, mMapH / 5);

	mainCharacter = new MainCharacter(nullptr,32*Game::getGame()->getScale(), 32 * Game::getGame()->getScale(), 32 * Game::getGame()->getScale(), 32 * Game::getGame()->getScale());

	camera->load();

	//level->getFirstRoom()->addCharacter(mainCharacter);//Se añade el personaje a la primera sala
	addGameObject(mainCharacter);


	//EnemyManager Requiere de MainCharacter : HACER DESPUES DE MAINCHARACTER
	EnemyManager::getInstance()->init(mainCharacter);
	CollisionsManager::getInstance();
	BulletManager::createInstance();
	LevelManager::getInstance()->getFirstRoom()->spawn();
	ItemManager::getInstance()->init();
	
	//Boss* boss = new Boss(mainCharacter, 300, 300, 200, 200);
	//addGameObject(boss);
	//ItemManager::getInstance()->AddItem(Enemies);
	HUDManager::getInstance()->init(mainCharacter);
}
