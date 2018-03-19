#include "MenuButton.h"
#include "ButtonRenderer.h"


MenuButton::MenuButton(Texture* normal, Texture* cursorOn, Texture* click, SDL_Rect r, CallBackOnClick* cb)
{
	ButtonRenderer br= new ButtonRenderer(normal, cursorOn, click, r)
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