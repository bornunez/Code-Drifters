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
	rect = skill_->GetSkillRect();
}


