#pragma once
#include "GameState.h"
class IntroState :
	public GameState
{
public:
	IntroState();
	virtual ~IntroState();
	virtual void render();
	virtual void update();
};

