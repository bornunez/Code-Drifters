#include "CreditsState.h"
#include "Game.h"
#include "Texture.h"



CreditsState::CreditsState()
{
	credits = new Texture(game->getRenderer(), "..\\images\\Creditos\\Creditos.png");
	rect = RECT(0, 0, game->getWinW(), 2550);
}


CreditsState::~CreditsState()
{
	delete credits;
}

void CreditsState::render()
{
	SDL_RenderClear(Game::getGame()->getRenderer());
	credits->render(rect);
}

void CreditsState::update()
{
	if (time < 43.5) {
		time += Time::getInstance()->DeltaTime;
		rect.y = 450 - time * 50;
	}
	else if (time < 51.5 && auxDegradado>0)
	{
		auxDegradado -= Time::getInstance()->DeltaTime/4;
		credits->setColor(auxDegradado * 125, auxDegradado * 125, auxDegradado * 125);
	}
	else 
	{
		game->endDialogue();
	}

	
}

void CreditsState::handleEvent(SDL_Event & e)
{
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_ESCAPE)
		{
			game->endDialogue();
		}
	}
}
