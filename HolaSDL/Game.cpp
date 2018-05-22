#pragma once
//#include "checkML.h"
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
#include "GameOverState.h"
#include "PauseState.h"
#include "Final.h"
#include "IntroState.h"
#include <iostream>
#include "CreditsState.h"
Game* Game::game = nullptr;

Game::Game()
{
}

void Game::ResetInstance()
{
	delete game;
	game = nullptr;
}

Game::~Game()

{	//Termina el juego llama a las destructoras de playState etc...
	endGame();
	delete stateMachine;			//Llama ademas a las destructoras de todos los estados que tenga pusheados
	PlayState::ResetInstance();
	delete Time::getInstance();

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::endGame()//Termina el PlayState y resetea sus instancias.
{
	saveConfig();
	delete mouseIcon;
	delete levP;
	//EnemyManager::ResetInstance();
	//PlayState::ResetInstance();			El destruir la pila llama a este destructor asi como al de mainmenu etc
	//BulletManager::ResetInstance();
	//LevelManager::ResetInstance();
	AnimationParser::deleteAnimationParser();
	ResourceManager::ResetInstance();

	//PRUEBA
	//PlayState::ResetInstance();
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

	SDL_SetRelativeMouseMode(SDL_TRUE);

	/*SDL_DisplayMode current;
	int display = SDL_GetCurrentDisplayMode(0, &current);

	window = SDL_CreateWindow("Neon Blade", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, current.w, current.h, SDL_WINDOW_SHOWN);*/

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Surface* icon = IMG_Load("..\\images\\bladeIcon.png");
	SDL_SetWindowIcon(window, icon);

	ResourceManager::createInstance(this->getRenderer());
	

	//Creamos el levelParser

	//Mouse Icon, maybe en playstate
	mouseIcon = new MouseIcon("..\\images\\mouseIcon.png");

	loadConfig();
	setWindow();
	setMute();
	
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
		/*	if (event.key.keysym.sym == SDLK_ESCAPE) {
				exit = true;
			}*/
			if (event.key.keysym.sym == SDLK_F11) {
				fullScreen = !fullScreen;
				setWindow();
			}
			/*else if (event.key.keysym.sym == SDLK_m) {
				mute = !mute;
				setMute();
			}*/
			/*else if (event.key.keysym.sym == SDLK_q) {
				endGame();
			}*/
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

void Game::flushEvents()
{
	while (SDL_PollEvent(&event)) {
	}
}

void Game::saveConfig()
{
	ofstream file;
	file.open("..\\config\\config.txt");

	file << ((fullScreen) ? "fullscreenTrue" : "fullscreenFalse") << endl;
	file << ((mute) ? "musicFalse" : "musicTrue") << endl;
	file << ((language == English) ? "ENG" : "ESP") << endl;
	file << ((cheats) ? "cheatsTrue" : "cheatsFalse") << endl;

	file.close();
}

void Game::loadConfig()
{
	ifstream file;
	file.open("..\\config\\config.txt");

	string fullscreenTxt;
	file >> fullscreenTxt;
	fullScreen = fullscreenTxt == "fullscreenTrue" ? true : false;

	string musicTxt;
	file >> musicTxt;
	mute = musicTxt == "musicTrue" ? false : true;
	
	string lang;
	file >> lang;
	language = lang == "ENG" ? English : Spanish;

	string cheatsTxt;
	file >> cheatsTxt;
	cheats = cheatsTxt == "cheatsTrue" ? true : false;

	file.close();
}

void Game::setWindow()
{
	if (fullScreen) {
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	}
	else {
		SDL_SetWindowFullscreen(window, SDL_FALSE);
	}
}
void Game::setMute()
{
	if (mute) {
		ResourceManager::getInstance()->muteMusic();
		ResourceManager::getInstance()->muteSoundEffect();
	}
	else {
		ResourceManager::getInstance()->unmuteMusic();
		ResourceManager::getInstance()->unmuteSoundEffect();
	}
}

void Game::muteGame()
{
	mute = !mute;
	setMute();
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

void Game::startGame(bool tutorial)
{
	playState = PlayState::getInstance();
	stateMachine->pushState(playState);
	playState->loadState(tutorial);
}


void Game::startDialogue(string filename)
{
	DialogsState* ds = new DialogsState(stateMachine->currentState(), filename);
	stateMachine->pushState(ds);
}

void Game::playIntro(bool tutorial)
{
	IntroState* is = new IntroState(tutorial);
	pushState(is);
}

void Game::endIntro(bool tutorial)
{
	stateMachine->popState();
	startGame(tutorial);
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

void Game::quitToMenu()
{
	ResourceManager::getInstance()->getMusic(Menu)->play();
	stateMachine->popState();
	stateMachine->popState();
	PlayState::ResetInstance();
	//EnemyManager::ResetInstance();
	//BulletManager::ResetInstance();
}
void Game::resetMenu()
{
	stateMachine->popState();
	stateMachine->pushState(new MainMenuState());
}


void Game::menuCredits()
{
	CreditsState* cs = new CreditsState();
	stateMachine->pushState(cs);
}

void Game::endCredits()
{
	quitToMenu();
	menuCredits();
}

void Game::pause(GameState* state)
{
	PauseState* pauseState = new PauseState(state);
	stateMachine->pushState(pauseState);
}

void Game::gameOver()
{
	GameOverState* go = new GameOverState();
	stateMachine->pushState(go);
}

void Game::restart()
{
	quitToMenu();
	startGame(PlayState::getInstance()->isTutorial());
}

void Game::final()
{
	Final* fin = new Final();
	stateMachine->pushState(fin);
}



