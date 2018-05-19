#pragma once
#include "GameState.h"
#include "Time.h"
class IntroState :
	public GameState
{
private:
	bool dialog1 = false;
	bool dialog2 = false;
	Texture* anim;
	float time;
	int frame=-1;
	float auxDegradado = 2;
	SDL_Rect destRect;
	SDL_Rect sourceRect;
public:
	IntroState();
	virtual ~IntroState();
	virtual void render();
	virtual void update();
	virtual void handleEvent(SDL_Event& e);
};

