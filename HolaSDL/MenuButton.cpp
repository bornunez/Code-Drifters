#include "MenuButton.h"
#include "ButtonRenderer.h"


MenuButton::MenuButton(Texture* normal, Texture* cursorOn, Texture* click, SDL_Rect r, CallBackOnClick* cb): rect(r)
{
	ButtonRenderer* br = new ButtonRenderer(this, normal, cursorOn, click, r);
	addComponent(br);
	callback = cb;
	pressed = false;
}


MenuButton::~MenuButton()
{
}

void MenuButton::render()
{
	GameObject::render();
}

void MenuButton::handleEvents(SDL_Event& e)
{
	SDL_GetMouseState(&mouse.x, &mouse.y);
	if (SDL_PointInRect(&mouse, &rect))
	{
		if (e.type = SDL_MOUSEBUTTONDOWN) 
		{
			sendMessage("pressed");
			pressed = true;
		}
		else if (e.type = SDL_MOUSEBUTTONUP && pressed) 
		{
			callback(game);
		}
	}
	else if (e.type = SDL_MOUSEBUTTONUP && pressed) 
	{
		sendMessage("released");
		pressed = false;
	}
	
}

void MenuButton::update() 
{
	SDL_GetMouseState(&mouse.x, &mouse.y);
	if (SDL_PointInRect(&mouse, &rect) && !cursorOn)
	{
		sendMessage("cursorOn");
	}
	else if(!SDL_PointInRect(&mouse, &rect) && cursorOn)
	{
		sendMessage("released");
	}
}