#pragma once
#include"SDL.h"
#include"SDL_image.h"
#include<iostream>
#include"Texture.h"
#include "GameObject.h"

using namespace std;

class Button: public GameObject
{
protected:
	typedef void CallBackOnClick();
	SDL_Rect destRect;
	CallBackOnClick* CbOnClk;

public:
	Button(SDL_Rect rect, CallBackOnClick cbon, string filename);
	~Button();
	bool HandleEvents(SDL_Event& e);
	void update();
};

