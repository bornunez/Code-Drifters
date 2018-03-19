#pragma once
#include "GameObject.h"
#include "Texture.h"
class ButtonRenderer;
class MenuButton : public GameObject
{
private:
	Texture* texture;
	SDL_Rect rect;
	typedef void CallBackOnClick(Game* game);
	CallBackOnClick* callback;
	SDL_Point mouse;
public:
	MenuButton(Texture* normal, Texture* cursorOn, Texture* click, SDL_Rect r, CallBackOnClick* cb);
	~MenuButton();
	void render();
	void handleEvents(SDL_Event& e);
	void update() {};
};