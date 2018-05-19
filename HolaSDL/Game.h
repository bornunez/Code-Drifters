#pragma once
//#include "checkML.h"
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

enum Language{ Spanish, English};
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
	bool fullScreen=false;
	bool mute = false;
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
	Language language = English;

	Game();
	~Game();
	void ResetInstance();

public:
	bool exit = false;
	SDL_Renderer* getRenderer();
	LevelParser* getLvlParser() { return levP; }
	void run();
	void handleEvents();
	void flushEvents();
	void saveConfig();
	void loadConfig();
	void setWindow();
	//Gets y sets
	const int getWorldWidth() const { return worldWidth; }
	const int getWorldHeight() const { return worldHeight; }
	int getScale() const { return scale; };
	int getWinW();
	int getWinH();
	int getLvl() { return level; }
	static Game* getGame();

	void startGame(bool tutorial);
	void setMute();
	Language getLanguage() { return language; }
	void setLanguage(Language lang) { language = lang; }
	string appendLanguage(string file) { if (language == English)file.append("_eng"); return file; }

	void endGame();
	void startDialogue(string filename);
	void endDialogue();
	void playIntro();
	void endIntro();
	void pushState(GameState* state);
	void quitState();
	void quitToMenu();
	void pause(GameState* state);
	void gameOver();
	void restart();
	void final();
};

