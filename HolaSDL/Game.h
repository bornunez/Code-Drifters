#pragma once
#include "sdl_includes.h"
#include <string>

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
class GameState;

using namespace std;
class Game
{
private:
	static Game* game;

	//Cosas de SDL
	SDL_Window* window;
	SDL_Renderer* renderer;
	//Camera* camera;
	bool error = false;//Flag para errores
	SDL_Event event;
	//Info de ventana
	int winX, winY;
	bool fullScreen;
	const int winWidth = 1020;
	const int winHeight = 720;
	//Info del juego
	const int scale = 3;
	const int worldWidth = 5000;
	const int worldHeight = 5000;
	int level;
	GameStateMachine* stateMachine;
	MouseIcon* mouseIcon;
	PlayState* playState;

	LevelParser* levP;


	Game();
	~Game();

public:
	bool exit = false;
	SDL_Renderer* getRenderer();
	LevelParser* getLvlParser() { return levP; }
	void run();
	void handleEvents();

	//Gets y sets
	const int getWorldWidth() const { return worldWidth; }
	const int getWorldHeight() const { return worldHeight; }
	int getScale() const { return scale; };
	int getWinW();
	int getWinH();
	int getLvl() { return level; }
	static Game* getGame();

	void startGame();
	void endGame();
	void startDialogue(string filename);
	void endDialogue();
	void pushState(GameState* state);
	void quitState();
	void quitToMenu();
};

