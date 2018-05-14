#pragma once
#include "GameObject.h"
#include "Texture.h"
class MenuButton : public GameObject
{
private:
	Texture* texture;
	SDL_Rect rect;
	typedef void CallBackOnClick(Game* game);
	CallBackOnClick* callback;
	SDL_Point mouse;
public:
	MenuButton(Texture* t, SDL_Rect r, CallBackOnClick* cb);
	virtual ~MenuButton();
	void render();
	void handleEvents(SDL_Event& e);
	void update() {};
};