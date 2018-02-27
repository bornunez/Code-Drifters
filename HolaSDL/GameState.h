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
	void cleanGarbage();
public:
	GameState();
	virtual ~GameState();
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void handleEvent(SDL_Event& e) = 0;
	void addGameObject(GameObject* go);
	void removeGameObject(GameObject* go);
};
