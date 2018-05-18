#pragma once
//#include "checkML.h"
#include "sdl_includes.h"
#include <list>
#include <queue>
#include "GameObject.h"

enum class StateType {RegularState, PlayState};
using namespace std;

class Game;
class GameState
{
private:
	queue<GameObject*>garbage;
protected:
	StateType stype = StateType::RegularState;
	list<GameObject*>gameObjects;
	Game* game;
	void cleanGarbage();
public:
	GameState();
	virtual ~GameState();
	virtual void update();
	virtual void render();
	virtual void lateRender();
	virtual void handleEvent(SDL_Event& e);
	void addGameObject(GameObject* go);
	void removeGameObject(GameObject* go);
	void destroyAllGameObjects();
	StateType getType() { return stype; };
};
