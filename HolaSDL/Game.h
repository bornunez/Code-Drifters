#pragma once
#include "sdl_includes.h"
#include "GameStateMachine.h"
#include "Camera.h"
#include "MainCharacter.h"
#include "DungeonGenerator.h"

using namespace std;
class Game
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Camera* camera;
	DungeonGenerator* level;
	bool error = false;//Flag para errores
	SDL_Event event;
	int winX, winY;
	const int winWidth = 1280;
	const int winHeight = 720;
	GameStateMachine* stateMachine;
	MainCharacter* mainCharacter;
public:

	DungeonGenerator * getLevel();
	MainCharacter * getCharacter();
	bool exit = false;
	Game();
	~Game();
	SDL_Renderer* getRenderer();
	Camera* getCamera();
	void run();
	void handleEvents();
	int getWinW();
	int getWinH();
};

