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
	GameState(Game* g) : game(g) {};
	virtual ~GameState();
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void handleEvent(SDL_Event& e) = 0;
	void addGameObject(GameObject* go);
	Game* getGame() { return this->game; }
	void removeGameObject(GameObject* go);
};
