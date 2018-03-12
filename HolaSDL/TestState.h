#pragma once
#include "GameState.h"
#include "sdl_includes.h"
#include <list>
#include "PlayState.h"

class Camera;
class Game;
class MainCharacter;
class DungeonGenerator;
class Enemy;

using namespace std;
class TestState : public GameState
{
private:
	Camera * camera;
	MainCharacter* mainCharacter;
	DungeonGenerator* level;



	//enemigo temporal
	Enemy* enemy;
	void loadState();
public:
	TestState(Game* g);
	virtual ~TestState();
	MainCharacter* getMainCharacter() { return mainCharacter; }
	virtual void render();
	virtual void handleEvent(SDL_Event& e);
	virtual void update();
	void addRoomObject(GameObject* o);
	DungeonGenerator* getLevel() { return this->level; }
	Camera* getCamera() { return this->camera; }
};

