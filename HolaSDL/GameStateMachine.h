
#pragma once
#include "sdl_includes.h"
#include <stack>
#include <queue>
#include "GameState.h"

class GameStateMachine
{

private:
	stack<GameState*>stateStack;
	queue<GameState*>garbage;

public:
	GameStateMachine();
	~GameStateMachine();
	GameState* currentState();
	void pushState(GameState* ge);
	void changeState(GameState* ge);
	void popState();

	void cleanGarbage();
};