
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
	void popState();//Saca un estado y lo borra
	void quitState();//Saca un estado pero no lo borra

	void cleanGarbage();
};