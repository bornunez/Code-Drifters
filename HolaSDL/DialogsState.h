#pragma once
#include "UpperGameState.h"
#include "DialogObject.h"

class DialogsState: public UpperGameState
{
public:
	DialogsState(GameState* inf, string filename);
	virtual ~DialogsState();
};

