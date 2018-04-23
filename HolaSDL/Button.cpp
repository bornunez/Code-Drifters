#include "Button.h"
#include "Game.h"



Button::Button(SkillTree* skill): skill_(skill)
{
}


Button::~Button()
{
}

void Button::handleEvents(SDL_Event& e) {
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		SDL_GetMouseState(&mouse.x, &mouse.y);
		if (SDL_PointInRect(&mouse, &rect))
		{
			skill_->Buy();
		}
	}
}

void Button::update()
{
	SDL_GetMouseState(&mouse.x, &mouse.y);
	if (SDL_PointInRect(&mouse, &rect)&& !cursorOn)
	{
		skill_->UpdateBox();
		cursorOn = true;
	}
	if (cursorOn && !SDL_PointInRect(&mouse, &rect)) 
	{
		skill_->DesactiveBox();
		cursorOn = false;
	}
	rect = skill_->GetSkillRect();
}


