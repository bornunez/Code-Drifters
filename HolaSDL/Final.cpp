#include "Final.h"
#include "Game.h"


Final::Final()
{
	tex = new Texture(game->getRenderer(), "..\\images\\ImFin.png", 1, 23);
	destRect = {70*game->getScale(), 30*game->getScale(), 200*game->getScale(), 200* game->getScale() };
	ResourceManager::getInstance()->getMusic(SadEnd)->play();
}


void Final::update()
{
	tiempo.update();
	sourceRect = { tex->getFrameWidth()*frame, 0, tex->getFrameWidth(), tex->getFrameHeight()};
	for (int i = 0; i < tex->getNumCols(); i++)
	{
		if (tiempo.TimeSinceTimerCreation >= i*0.125f)
		{
			frame = 2 + i;
		}
	}
	if (frame >= tex->getNumCols()-1 && auxDegradado > 0)
	{
		auxDegradado -= Time::getInstance()->DeltaTime;
		tex->setColor(auxDegradado * 125, auxDegradado * 125, auxDegradado * 125);
	}
	else if(frame >= tex->getNumCols() - 1)
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
}
