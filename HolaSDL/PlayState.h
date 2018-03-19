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

using namespace std;
class PlayState : public GameState
{
private:
	Camera * camera;
	MainCharacter* mainCharacter;
	Game* game;
	DungeonGenerator* level;
	Room* currentRoom;
	GameManager* gameManager;


	//enemigo temporal
	ExampleEnemy* enemy;
public:
	PlayState();
	void loadState();
	~PlayState();
	MainCharacter* getMainCharacter() { return mainCharacter; }
	void render();
	void handleEvent(SDL_Event& e);
	void update();	
	DungeonGenerator* getLevel() { return this->level; }
	Camera* getCamera() { return this->camera; }
};

