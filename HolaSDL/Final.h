#pragma once
#include "GameState.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Timer.h"
#include "Time.h"
class Final: public GameState
{
private:
	bool sonado = false;
	float degradado = 1;
	float auxDegradado = 1;
	float auxPaso = 2;
public:
	Timer tiempo;
	Texture* tex;
	int frame;
	SDL_Rect destRect;
	SDL_Rect sourceRect;
	Final();
	~Final();
	virtual void update();
	virtual void render();
};

