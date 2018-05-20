#pragma once
#include "GameState.h"
#include "Time.h"
class CreditsState :
	public GameState
{
private:
	Texture* credits;
	float time;
	SDL_Rect rect;
	float auxDegradado = 2;
public:
	CreditsState();
	virtual ~CreditsState();

	virtual void render();
	virtual void update();
	virtual void handleEvent(SDL_Event& e);
};

