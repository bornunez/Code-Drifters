#pragma once
#include "GameStateMachine.h"
GameStateMachine::GameStateMachine()
{

}
GameStateMachine::~GameStateMachine()
{
	while (!stateStack.empty())
	{
		GameState* gs = stateStack.top();
		stateStack.pop();
		delete gs;
	}
}

GameState* GameStateMachine::currentState()
{
	return stateStack.top();
}



void GameStateMachine::pushState(GameState* ge)
{
	stateStack.push(ge);
}



GameState* GameStateMachine::popState()
{
	GameState* gs = stateStack.top();
	stateStack.pop();
	return gs;
}

void GameStateMachine::changeState(GameState* ge)
{
	GameState* gs = popState();
	delete gs;
	pushState(ge);
}