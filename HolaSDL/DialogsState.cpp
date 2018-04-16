#include "DialogsState.h"



DialogsState::DialogsState(GameState* inf, string filename): UpperGameState(inf)
{
	DialogObject* d = new DialogObject(filename);
	gameObjects.push_back(d);
}


DialogsState::~DialogsState()
{
}
