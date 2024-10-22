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
#include <fstream>
#include "ShopState.h"

#include"HUDManager.h"
#include "ParticlesManager.h"

PlayState* PlayState::instance = nullptr;

PlayState::PlayState():GameState ()
{
	ResourceManager::getInstance()->getMusic(Level1)->play();
	stype = StateType::PlayState;
}

void PlayState::ResetInstance()
{
	if (instance != nullptr) {
		delete instance; // REM : it works even if the pointer is NULL (does nothing then)
		instance = nullptr; // so GetInstance will still work.
	}
	
}

PlayState::~PlayState()
{
	CollisionsManager::ResetInstance();
	BulletManager::ResetInstance();
	ItemManager::ResetInstance();
	EnemyManager::ResetInstance();
	CoinManager::ResetInstance();
	HUDManager::ResetInstance();
	ParticlesManager::ResetInstance();
	LevelManager::ResetInstance();
	
	delete shopState;
	delete minimap;
	delete camera;
	//delete level;
	//delete currentRoom;
	instance->destroyAllGameObjects();
	//MainCharacter se borra en el destroyAllGameObjects
}

PlayState * PlayState::getInstance()
{
	if (instance == nullptr)
		instance = new PlayState();
	return instance;
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
	LevelManager::getInstance()->lateRender();
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
		if (e.key.keysym.sym == SDLK_ESCAPE)
		{
			game->pause(this);
		}
		
	}
	GameState::handleEvent(e);
	LevelManager::getInstance()->handleEvents(e);
	//mainCharacter->handleEvents(e);
}

void PlayState::update()
{
	EnemyManager::getInstance()->update();
	GameState::update();
	CoinManager::getInstance()->update();
	BulletManager::getInstance()->update();
	LevelManager::getInstance()->update();
	//level->getRoom(mainCharacter->getCurrentRoomX(), mainCharacter->getCurrentRoomY())->update();//Hace el update de la sala actual	
	HUDManager::getInstance()->update(); //de momento peta
	CollisionsManager::getInstance()->update();
	camera->update();
}

void PlayState::nextLevel()
{
	//Creamos el puntero, es todo lo que hace falta
	delete camera;
	camera = new Camera();

	//IMPORTANTE: Crear primero la camara. El mapa la requiere
	LevelManager::getInstance()->nextLevel();
	delete minimap;
	minimap = new Minimap(1, 1, 10, 10);

	camera->load();
	LevelManager::getInstance()->enterMap();
	//Al final ajustamos el deltaTime
	Time::getInstance()->DeltaTime = 0.001;
	Game::getGame()->flushEvents();
	//HUDManager::getInstance()->addBullet();
	//Boss* boss = new Boss(mainCharacter, 600, 600, 200, 200);
	//addGameObject(boss);
}

void PlayState::openShop()
{
	game->pushState(shopState);
}

void PlayState::endState()
{
	//delete camera;
	//delete mainCharacter;
	//delete level;
	//delete currentRoom;
	//delete minimap;
	//delete shopState;
	
	/*camera = nullptr;
	mainCharacter = nullptr;
	EnemyManager::getInstance()->killAll();
	destroyAllGameObjects();*/
}

void PlayState::loadState(bool tutorial)
{
	tuto = tutorial;
	if (!tuto) {
		ifstream tuto_file;
		tuto_file.open("..\\levels&tiles\\Tutorial\\tutorial_done");
		if (tuto_file.is_open()) {
			tuto = false;
			tuto_file.close();
		}
		else
			tuto = true;
	}
	//Creamos el puntero, es todo lo que hace falta
	camera = new Camera();

	//IMPORTANTE: Crear primero la camara. El mapa la requiere
	LevelManager::getInstance()->init(tutorial);
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

	//Al final ajustamos el deltaTime
	Time::getInstance()->DeltaTime = 0.001;
	Game::getGame()->flushEvents();
	//HUDManager::getInstance()->addBullet();
	//Boss* boss = new Boss(mainCharacter, 600, 600, 200, 200);
	//addGameObject(boss);
}
