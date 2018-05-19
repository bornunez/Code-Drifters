#pragma once
#include "GameState.h"
#include "Texture.h"
#include "ResourceManager.h"
//#include "Timer.h"
class Final: public GameState
{
public:
	//Timer* tiempo;
	Texture* tex;
	//int frame;
	//SDL_Rect destRect;
	//SDL_Rect sourceRect;
	Final();
	~Final();
	virtual void update();
	virtual void render();
};

