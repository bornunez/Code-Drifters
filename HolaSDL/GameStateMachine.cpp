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



void GameStateMachine::popState()
{
	GameState* gs = stateStack.top();
	stateStack.pop();
	garbage.push(gs);
}

void GameStateMachine::changeState(GameState* ge)
{
	popState();
	pushState(ge);
}

void GameStateMachine::cleanGarbage() 
{
	GameState* aux= garbage.front();
	garbage.pop();
	if (aux != nullptr) 
	{
		delete aux;
	}
}