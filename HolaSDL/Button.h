#pragma once
#include"SDL.h"
#include"SDL_image.h"
#include<iostream>
#include"Texture.h"

using namespace std;

class Button
{
protected:
	typedef void CallBackOnClick();
	SDL_Rect destRect;
	CallBackOnClick* CbOnClk;

	SDL_Renderer* rend_;

	Texture* text;

public:
	Button(SDL_Rect rec, CallBackOnClick cbon, string filename, SDL_Renderer* rend);
	~Button();
	bool HandleEvents(SDL_Event& e);
	void update();
	void render(SDL_Renderer* rend, SDL_Rect destRec);
	void render();
};

