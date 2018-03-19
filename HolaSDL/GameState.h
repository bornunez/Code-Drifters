#pragma once
#include "sdl_includes.h"
#include <list>
#include <queue>
#include "GameObject.h"


using namespace std;

class Game;
class GameState
{
private:
	queue<GameObject*>garbage;
protected:
	list<GameObject*>gameObjects;
	Game* game;
	void cleanGarbage();
public:
	GameState();
	virtual ~GameState();
	virtual void update();
	virtual void render();
	virtual void handleEvent(SDL_Event& e);
	void addGameObject(GameObject* go);
	void removeGameObject(GameObject* go);
};
