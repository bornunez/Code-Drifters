#pragma once
#include "sdl_includes.h"
#include <vector>
#include "GameObject.h"


using namespace std;

class Game;
class GameState
{
protected:
	vector<GameObject*>gameObjects;

public:
	GameState();
	virtual ~GameState();
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void handleEvent(SDL_Event& e) = 0;
};
