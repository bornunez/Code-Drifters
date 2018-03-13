#include "MenuButton.h"
#include "Game.h"


MenuButton::MenuButton(Texture* t, SDL_Rect r, CallBackOnClick* cb)
{
	texture = t;
	rect = r;
	callback = cb;
}


MenuButton::~MenuButton()
{
}

void MenuButton::render()
{
	texture->render(rect);
}

void MenuButton::handleEvents(SDL_Event& e)
{
	SDL_GetMouseState(&mouse.x, &mouse.y);
	if (SDL_PointInRect(&mouse, &rect))
	{
		callback(game);
	}
}