#pragma once
#include "GameStateMachine.h"
GameStateMachine::GameStateMachine()
{

}
GameStateMachine::~GameStateMachine()
{
	while (!stateStack.empty())
	{
		popState();
	}
	//cleanGarbage();
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
	if (!stateStack.empty()) {
		GameState* top = stateStack.top();
		stateStack.pop();
		delete top;
	}

	/*GameState* gs = stateStack.top();
	stateStack.pop();
	garbage.push(gs);*/
}

void GameStateMachine::quitState()
{
	stateStack.pop();
}

void GameStateMachine::changeState(GameState* ge)
{
	popState();
	pushState(ge);
}

void GameStateMachine::cleanGarbage() 
{
	while (!garbage.empty())
	{
		GameState* aux = garbage.front();
		garbage.pop();

		if (aux != nullptr)
		{
			delete aux;
		}
	}
}