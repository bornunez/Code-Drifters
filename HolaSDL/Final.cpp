#include "Final.h"
#include "Game.h"


Final::Final()
{
	tex = ResourceManager::getInstance()->getTexture(TextureId::ImFin);
}


void Final::update()
{

}

void Final::render()
{
	SDL_RenderClear(Game::getGame()->getRenderer());
	tex->render(0, 0);
}


Final::~Final()
{
}
