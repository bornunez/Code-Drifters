#include "Button.h"
#include "Game.h"



Button::Button(SDL_Rect rect, CallBackOnClick cbon, string filename)
{
	CbOnClk = cbon;
	destRect = rect;
}


Button::~Button()
{
}

bool Button::HandleEvents(SDL_Event& e) {
	bool handled = false;
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		SDL_Point p;
		SDL_GetMouseState(&p.x, &p.y);
		if (SDL_PointInRect(&p, &destRect)) {
			handled = true;
			CbOnClk();
		}
	}
	return handled;
}

void Button::update() {}

