#include "Final.h"
#include "Game.h"


Final::Final()
{
	tex = new Texture(game->getRenderer(), "..\\images\\ImFin.png", 1, 20);
	tiempo = new Timer();
	destRect = {70*game->getScale(), 30*game->getScale(), 200*game->getScale(), 200* game->getScale() };
	ResourceManager::getInstance()->getMusic(SadEnd)->play();
}


void Final::update()
{
	tiempo->update();
	sourceRect = { tex->getFrameWidth()*frame, 0, tex->getFrameWidth(), tex->getFrameHeight()};
	if (tiempo->TimeSinceTimerCreation > 2 && tiempo->TimeSinceTimerCreation < 3 && auxDegradado > 0)
	{
		auxDegradado -= Time::getInstance()->DeltaTime;
		tex->setColor(auxDegradado*125, auxDegradado*125, auxDegradado*125);
	}
	else if (tiempo->TimeSinceTimerCreation > 3 && tiempo->TimeSinceTimerCreation < 4 && auxDegradado < degradado)
	{
		auxDegradado += Time::getInstance()->DeltaTime;
		frame = 1;
		tex->setColor(auxDegradado * 125, auxDegradado * 125, auxDegradado * 125);
	}
	else if (tiempo->TimeSinceTimerCreation > 4 && tiempo->TimeSinceTimerCreation < 4.5f && auxDegradado > 0)
	{
		frame = 1;
		auxDegradado -= Time::getInstance()->DeltaTime;
		tex->setColor(auxDegradado * 255, auxDegradado * 255, auxDegradado * 255);

		if (!sonado)
		{
			ResourceManager::getInstance()->getSoundEffect(SwordSlash)->play();
			sonado = true;
		}
	}
	else if (tiempo->TimeSinceTimerCreation > 4.5 && tiempo->TimeSinceTimerCreation < 6 && auxDegradado < degradado)
	{
		frame = 2;
		auxDegradado += Time::getInstance()->DeltaTime;
		tex->setColor(auxDegradado * 125, auxDegradado * 125, auxDegradado * 125);
	}
	for (int i = 0; i < 17; i++)
	{
		if (!luminoso)
		{
			tex->setColor(225, 225, 225);
			luminoso = true;
		}
		if (tiempo->TimeSinceTimerCreation > 6 + (i*0.125f) && frame < 19)
		{
			frame = 2 + i;
		}
	}
	if (frame >= 17 && auxDegradado > 0)
	{
		auxDegradado -= Time::getInstance()->DeltaTime;
		tex->setColor(auxDegradado * 125, auxDegradado * 125, auxDegradado * 125);
	}
	else if(frame >= 17)
	{
		auxDegradado = 0;
		tex->setColor(auxDegradado * 125, auxDegradado * 125, auxDegradado * 125);
	}
}

void Final::render()
{
	SDL_RenderClear(Game::getGame()->getRenderer());
	tex->render(destRect, 0, &sourceRect);
}


Final::~Final()
{
	delete tex;
	delete tiempo;
}
