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
	DungeonGenerator* level;
	Room* currentRoom;

	static PlayState* instance;


	//enemigo temporal
	ExampleEnemy* enemy;
	PlayState();
public:
	void loadState();
	static PlayState* getInstance();
	~PlayState();
	MainCharacter* getMainCharacter() { return mainCharacter; }
	virtual void render();
	virtual void handleEvent(SDL_Event& e);
	virtual void update();
	void addRoomObject(GameObject* o);	
	DungeonGenerator* getLevel() { return this->level; }
	Camera* getCamera() { return this->camera; }
	Room* getCurrentRoom();
};

