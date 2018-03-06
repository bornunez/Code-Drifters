#pragma once
#include "sdl_includes.h"

class MouseIcon;
class ResourceManager;
class ExampleEnemy;
class MainCharacter;
class DungeonGenerator;
class CameraMovementComponent;
class MCMovementComponent;
class GameStateMachine;
class Camera;
class Map;
class LevelParser;
class PlayState;

using namespace std;
class Game
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	//Camera* camera;
	ResourceManager* resourceManager;
	bool error = false;//Flag para errores
	SDL_Event event;
	int winX, winY;
	bool fullScreen;
	const int winWidth = 1020;
	const int winHeight = 720;
	const int worldWidth = 5000;
	const int worldHeight = 5000;
	GameStateMachine* stateMachine;
	MouseIcon* mouseIcon;
	PlayState* playState;

	LevelParser* levP;

public:
	bool exit = false;
	Game();
	~Game();
	SDL_Renderer* getRenderer();
	ResourceManager* getResourceManager() { return resourceManager; }
	LevelParser* getLvlParser() { return levP; }
	void run();
	void handleEvents();
	const int getWorldWidth() const { return worldWidth; }
	const int getWorldHeight() const { return worldHeight; }
	int getWinW();
	int getWinH();
};

