#pragma once
#include "Game.h"
#include "GameStateMachine.h"
#include "Camera.h"
#include "MainCharacter.h"
#include "DungeonGenerator.h"
#include "CameraMovementComponent.h"
#include "ExampleEnemy.h"
#include "ResourceManager.h"
#include "MouseIcon.h"
#include "MCMovementComponent.h"
#include "DungeonGenerator.h"
#include "Room.h"
<<<<<<< HEAD
#include "ChaseComponent.h"
#include "Boss.h"

DungeonGenerator * Game::getLevel()
{
	return level;
}

MainCharacter * Game::getCharacter()
{
	return mainCharacter;
}
=======
#include "LevelParser.h"
#include "Map.h"
#include "PlayState.h"
>>>>>>> master

Game::Game()
{
	winX = winY = 100;
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_ShowCursor(SDL_DISABLE);
	window = SDL_CreateWindow("Haro I de Saboya", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	resourceManager = new ResourceManager(this->getRenderer());
	//Creamos el levelParser

	//Mouse Icon, maybe en playstate
	mouseIcon = new MouseIcon(this, "..\\images\\mouseIcon.png");


<<<<<<< HEAD
	//Enemy (test)
	enemy = new Enemy(this, mainCharacter, 50, 50, 20, 20);
	enemyChaseComponent = new ChaseComponent(enemy, mainCharacter, 0.1);
	enemy->addComponent(enemyChaseComponent);
	level->getFirstRoom()->addCharacter(enemy);
	boss = new Boss(this, mainCharacter, 400, 100, 100, 100);
	level->getFirstRoom()->addCharacter(boss);
=======
	//Esto deber?a ir en el playState, est? puesto de prueba. Crea un personaje y una c?mara, le asigna una sala al personaje

>>>>>>> master

	if (renderer == nullptr)//Si hay errores activa el flag
	{
		error = true;
	}
	else
	{
		resourceManager = new ResourceManager(this->getRenderer());
		stateMachine = new GameStateMachine();
		PlayState* ps = new PlayState(this);
		stateMachine->pushState(ps);
		//Mouse Icon, maybe en playstate
		levP = new LevelParser();
		mouseIcon = new MouseIcon(this, "..\\images\\mouseIcon.png");

		//Este int no se que pinta aqui
		int roomNumber = 20;
		//MainMenuState* mm = new MainMenuState(this);
		//stateMachine->pushState(mm);

	}
}
Game::~Game()
{
	delete stateMachine;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}

SDL_Renderer * Game::getRenderer()
{
	return renderer;
}


void Game::run()
{
	while (!exit) 
	{
		//Provisional en lugar del render
	
		stateMachine->currentState()->update();
		stateMachine->currentState()->render();
		handleEvents();
<<<<<<< HEAD
		mainCharacter->update();//Provisional en lugar del update
		enemy->update();
		camera->update();
		boss->update();
=======
		this->mouseIcon->drawIcon(event);
		SDL_RenderPresent(this->getRenderer());
>>>>>>> master
	}
}

void Game::handleEvents()
{
	while (SDL_PollEvent(&event) && !exit) {

		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				exit = true;
			}
			else if (event.key.keysym.sym == SDLK_F11) {
				
				if (fullScreen) {
					fullScreen = false;
					SDL_SetWindowFullscreen(window, SDL_FALSE);					
				}
				else {
					fullScreen = true;
					SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
				}
			}
		}
		if (event.type == SDL_QUIT)
		{
			exit = true;
		}

		else
		{
			stateMachine->currentState()->handleEvent(event);
		}
	}
}

int Game::getWinW() {//Pide el ancho de la ventana
	return winWidth;
}
int Game::getWinH() {//Pide la altura de la altura
	return winHeight;
}

