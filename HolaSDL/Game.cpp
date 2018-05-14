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
#include "DungeonGenerator.h"
#include "Room.h"
#include "LevelParser.h"
#include "Map.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "Time.h"
#include "LevelManager.h"
#include "DialogsState.h"

Game* Game::game = nullptr;

Game::Game()
{
}

void Game::ResetInstance()
{
	delete game;
	game = NULL;
}

Game::~Game()

{	//Termina el juego llama a las destructoras de playState etc...
	endGame();
	delete stateMachine;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}

void Game::endGame()//Termina el PlayState y resetea sus instancias.
{
	delete mouseIcon;
	delete levP;
	EnemyManager::ResetInstance();
	PlayState::ResetInstance();
	BulletManager::ResetInstance();
	LevelManager::ResetInstance();
	ResourceManager::ResetInstance();
	stateMachine->popState();
}


SDL_Renderer * Game::getRenderer()
{
	return renderer;
}


void Game::run()
{
	winX = winY = 100;
	SDL_Init(SDL_INIT_EVERYTHING);

	//SDL Fonts
	TTF_Init();

	// SDL Mixer (Music, Sound, etc)
	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	SDL_ShowCursor(SDL_DISABLE);
	window = SDL_CreateWindow("Neon Blade", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Surface* icon = IMG_Load("..\\images\\bladeIcon.png");
	SDL_SetWindowIcon(window, icon);

	ResourceManager::createInstance(this->getRenderer());
	

	//Creamos el levelParser

	//Mouse Icon, maybe en playstate
	mouseIcon = new MouseIcon("..\\images\\mouseIcon.png");
	
	//Esto deber?a ir en el playState, est? puesto de prueba. Crea un personaje y una c?mara, le asigna una sala al personaje


	if (renderer == nullptr)//Si hay errores activa el flag
	{
		error = true;
	}
	else
	{
		stateMachine = new GameStateMachine();
		
		//playState->loadState();
		//stateMachine->pushState(playState);
		MainMenuState* mm = new MainMenuState();
		stateMachine->pushState(mm);
		//Mouse Icon, maybe en playstate
		levP = new LevelParser();

		//Este int no se que pinta aqui
		int roomNumber = 20;
		//MainMenuState* mm = new MainMenuState(this);
		//stateMachine->pushState(mm);

	}

	while (!exit) 
	{
		Time::getInstance()->Ticks();
		//Provisional en lugar del render	
		handleEvents();
		stateMachine->currentState()->update();
		stateMachine->currentState()->render();
		stateMachine->currentState()->lateRender();
		this->mouseIcon->drawIcon(event);
		SDL_RenderPresent(this->getRenderer());
	}
	//Sale del juego liberando la memoria ocupada.
	ResetInstance();
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
			else if (event.key.keysym.sym == SDLK_q) {
				endGame();
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

Game * Game::getGame()
{
	if (!game)
		game = new Game();
	return game;
}

void Game::startGame()
{
	playState = PlayState::getInstance();
	stateMachine->pushState(playState);
	playState->loadState();
}


void Game::startDialogue(string filename)
{
	DialogsState* ds = new DialogsState(stateMachine->currentState(), filename);
	stateMachine->pushState(ds);
}

void Game::endDialogue() 
{
	stateMachine->popState();
}

void Game::pushState(GameState * state)
{
	stateMachine->pushState(state);
}

void Game::quitState()
{
	stateMachine->quitState();
}


