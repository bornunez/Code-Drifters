#pragma once
#include "GameState.h"
#include "sdl_includes.h"
#include <list>

class Camera;
class Game;
class MainCharacter;
class DungeonGenerator;
class ExampleEnemy;
class Room;
class Minimap;

using namespace std;
class PlayState : public GameState
{
private:
	Camera * camera;
	MainCharacter* mainCharacter;
	DungeonGenerator* level;
	Room* currentRoom;
	Minimap* minimap;

	static PlayState* instance;

	GameState* shopState;
	//enemigo temporal
	PlayState();
public:
	void loadState();
	static PlayState* getInstance();
	static void ResetInstance();
	~PlayState();
	MainCharacter* getMainCharacter() { return mainCharacter; }
	void render();
	void handleEvent(SDL_Event& e);
	void update();	
	DungeonGenerator* getLevel() { return this->level; }
	Camera* getCamera() { return this->camera; }
	void openShop();
	void endState();
};

