#pragma once
#include "GameState.h"
#include "sdl_includes.h"
#include <list>

class Camera;
class Game;
class MainCharacter;
class DungeonGenerator;
class Enemy;

using namespace std;
class PlayState : public GameState
{
private:
	Camera * camera;
	MainCharacter* mainCharacter;
	DungeonGenerator* level;

	list<GameObject*> sceneObjects;


	//enemigo temporal
	Enemy* enemy;
	void loadState();
public:
	PlayState(Game* g);
	~PlayState();
	MainCharacter* getMainCharacter() { return mainCharacter; }
	virtual void render();
	virtual void handleEvent(SDL_Event& e);
	virtual void update();
	void addSceneObject(GameObject* o);
	DungeonGenerator* getLevel() { return this->level; }
	Camera* getCamera() { return this->camera; }
};

