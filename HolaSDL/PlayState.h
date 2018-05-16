#pragma once
#include "checkML.h"
#include "GameState.h"
#include "sdl_includes.h"
#include "Boss.h"
#include <list>

class Camera;
class Game;
class MainCharacter;
class DungeonGenerator;
class ExampleEnemy;
class Room;
class Minimap;

//class HUDManager;

using namespace std;
class PlayState : public GameState
{
private:
	Camera * camera;
	MainCharacter* mainCharacter;
	DungeonGenerator* level;
	Room* currentRoom;
	Minimap* minimap;


	//HUDManager* hud;

	static PlayState* instance;

	GameState* shopState;
	//enemigo temporal
	PlayState();
public:
	void loadState(bool tutorial);
	static PlayState* getInstance();
	static void ResetInstance();
	virtual ~PlayState();

	void render();
	void lateRender();
	void handleEvent(SDL_Event& e);
	void update();	

	void nextLevel();

	MainCharacter* getMainCharacter() { return mainCharacter; }
	DungeonGenerator* getLevel() { return this->level; }
	Camera* getCamera() { return this->camera; }
	void openShop();
	void endState();
};

