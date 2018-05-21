#include "Final.h"
#include "Game.h"


Final::Final()
{
	tex = new Texture(game->getRenderer(), "..\\images\\ImFin.png", 1, 23);
	destRect = {70*game->getScale(), 30*game->getScale(), 200*game->getScale(), 200* game->getScale() };
	ResourceManager::getInstance()->getMusic(FinalBoss2)->stop();
}


void Final::update()
{
	tiempo.update();
	sourceRect = { tex->getFrameWidth()*frame, 0, tex->getFrameWidth(), tex->getFrameHeight()};
	for (int i = 0; i < tex->getNumCols(); i++)
	{
		if (tiempo.TimeSinceTimerCreation > 0.5f &&  tiempo.TimeSinceTimerCreation >= i*0.13f+0.5f)
		{
			frame = i;
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
	if (frame >= tex->getNumCols() - 1)
	{
		auxPaso -= Time::getInstance()->DeltaTime;
	}
	if (auxPaso <= 0)
	{
		Game::getGame()->endCredits();
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
