#pragma once
#include "GameState.h"
#include "Time.h"
class IntroState :
	public GameState
{
private:
	bool dialog1 = false;
	bool dialog2 = false;
	bool tutorial_;
	Texture* anim;
	float time;
	int frame=-1;
	float auxDegradado = 2;
	SDL_Rect destRect;
	SDL_Rect sourceRect;
	string rute;
	string rute2;
public:
	IntroState(bool tutorial);
	virtual ~IntroState();
	virtual void render();
	virtual void update();
	virtual void handleEvent(SDL_Event& e);
};

