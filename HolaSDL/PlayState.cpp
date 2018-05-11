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
#include "CoinManager.h"
#include "ItemManager.h"
#include "ShopState.h"

#include"HUDManager.h"
#include "ParticlesManager.h"

PlayState* PlayState::instance = nullptr;

PlayState::PlayState():GameState ()
{
	ResourceManager::getInstance()->getMusic(Music1)->play();

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
	CoinManager::getInstance()->render();
	BulletManager::getInstance()->render();
	//Aqui se pinta el prota
	GameState::render();
	minimap->render();
	ItemManager::getInstance()->render();
	HUDManager::getInstance()->render();
	ParticlesManager::getInstance()->render();
}

void PlayState::lateRender()
{
	GameState::lateRender();
	EnemyManager::getInstance()->lateRender();
}

void PlayState::handleEvent(SDL_Event & e)
{
	if (e.type == SDL_KEYDOWN)//Provisional para debug de dialogos
	{
		if (e.key.keysym.sym == SDLK_l)
		{
			game->startDialogue("1");
		}
		if (e.key.keysym.sym == SDLK_o)
		{
			openShop();
		}
	}
	GameState::handleEvent(e);
	//mainCharacter->handleEvents(e);
}

void PlayState::update()
{
	EnemyManager::getInstance()->update();
	GameState::update();
	CoinManager::getInstance()->update();
	BulletManager::getInstance()->update();
	//level->getRoom(mainCharacter->getCurrentRoomX(), mainCharacter->getCurrentRoomY())->update();//Hace el update de la sala actual	
	//cout << enemy->getTransform()->position;
	HUDManager::getInstance()->update(); //de momento peta
	CollisionsManager::getInstance()->update();
	camera->update();
}

void PlayState::openShop()
{
	game->pushState(shopState);
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
	minimap = new Minimap(1,1, 10, 10);

	mainCharacter = new MainCharacter(nullptr,32*Game::getGame()->getScale(), 32 * Game::getGame()->getScale(), 32 * Game::getGame()->getScale(), 32 * Game::getGame()->getScale());
	shopState = new ShopState(this);
	camera->load();

	//level->getFirstRoom()->addCharacter(mainCharacter);//Se añade el personaje a la primera sala
	addGameObject(mainCharacter);


	//EnemyManager Requiere de MainCharacter : HACER DESPUES DE MAINCHARACTER
	EnemyManager::getInstance()->init(mainCharacter);
	CollisionsManager::getInstance();
	BulletManager::createInstance();
	LevelManager::getInstance()->enterMap();
	ItemManager::getInstance()->init();
	CoinManager::getInstance();
	//ItemManager::getInstance()->AddItem(Enemies);
	HUDManager::getInstance()->init(mainCharacter);
	//HUDManager::getInstance()->addBullet();
	//Boss* boss = new Boss(mainCharacter, 600, 600, 200, 200);
	//addGameObject(boss);
}
