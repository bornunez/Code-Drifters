#pragma once
#include "sdl_includes.h"
#include "GameStateMachine.h"
#include "Camera.h"
#include "MainCharacter.h"
#include "DungeonGenerator.h"
#include "CameraMovementComponent.h"
#include "Enemy.h"

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
	bool fullScreen;
	const int winWidth = 1020;
	const int winHeight = 720;
	const int worldWidth = 100000;
	const int worldHeight = 100000;
	GameStateMachine* stateMachine;
	MainCharacter* mainCharacter;
	MCMovementComponent* mainCharacterMovement;

	Enemy* enemy;
	ChaseComponent* enemyChaseComponent;

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
	const int getWorldWidth() { return worldWidth; }
	const int getWorldHeight() { return worldHeight; }
	int getWinW();
	int getWinH();
};

