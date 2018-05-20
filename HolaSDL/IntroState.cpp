#include "IntroState.h"
#include "Game.h"
#include "ResourceManager.h"



IntroState::IntroState()
{
	anim = new Texture(game->getRenderer(), "..\\images\\ImIntro.png", 1, 20);
	destRect = RECT(0, 0, game->getWinW(), game->getWinH());
	if (game->getLanguage() == Language::English)
	{
		rute = "intro1_eng";
		rute2 = "intro2_eng";
	}
	else
	{
		rute = "intro1";
		rute2 = "intro2";
	}
}


IntroState::~IntroState()
{
	delete anim;

}

void IntroState::render()
{
	SDL_RenderClear(Game::getGame()->getRenderer());
	if (dialog1)
	{
		sourceRect = { anim->getFrameWidth()*frame, 0, anim->getFrameWidth(), anim->getFrameHeight() };
		anim->render(destRect, 0, &sourceRect);
	}
}

void IntroState::update()
{
	if (dialog1 && !dialog2)
	{
		time += Time::getInstance()->DeltaTime;
		if (frame == -1) {
			frame = 0;
		}
		if (time < 1.6)
		{
 			frame = time /0.1;
		}
		if (time > 1.7)
		{
			game->startDialogue(rute2);
			dialog2 = true;
			time = 0;
		}
	}
	else if (dialog1 && dialog2)
	{
		time += Time::getInstance()->DeltaTime;
		if (frame < 16)
		{
			frame = 16;
		}
		else if (time > 1.2) 
		{
			frame = 19;
		}
		if (frame ==19 && time>1.7&&auxDegradado >0)
		{
			auxDegradado -= Time::getInstance()->DeltaTime;
			anim->setColor(auxDegradado * 125, auxDegradado * 125, auxDegradado * 125);
		}
		else if (frame == 19 && time>1.7)
		{
			game->endIntro();
		}
	}
	if(!dialog1 && !dialog2){
		game->startDialogue(rute);
		dialog1 = true;
	}
}

void IntroState::handleEvent(SDL_Event & e)
{
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_ESCAPE)
		{
			game->endIntro();
		}
	}
}
