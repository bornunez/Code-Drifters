#include "Button.h"



Button::Button(SDL_Rect rec, CallBackOnClick cbon, string filename, SDL_Renderer* rend)
{
	CbOnClk = cbon;
	destRect = rec;
	text = new Texture();
	rend_ = rend;
	text->loadText(filename, 1, 1, rend_);
}


Button::~Button()
{
	delete text;
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

void Button::render(SDL_Renderer* render, SDL_Rect destRec) {
	destRect = destRec;
	rend_ = render;
	text->Render(destRec, render);
}

void Button::render() {
	text->Render(destRect, rend_);
}
