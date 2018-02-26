#pragma once
#include "sdl_includes.h"
#include "GameStateMachine.h"

using namespace std;
class Game
{
private:
	SDL_Window* window;
	bool error = false;//Flag para errores
	SDL_Event event;
	int winX, winY;
	const int winWidth = 1280;
	const int winHeight = 720;
	GameStateMachine* stateMachine;
public:
	bool exit = false;

	SDL_Renderer* renderer;
	Game();
	~Game();

	void run();
	void handleEvents();
	int getWinW();
	int getWinH();
};

