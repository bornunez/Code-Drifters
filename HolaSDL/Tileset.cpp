#include "Tileset.h"



Tileset::Tileset(std::string src) : srcFile(src)
{
}

SDL_Rect Tileset::getTileRect(int tileID)
{
	SDL_Rect srcRect;
	srcRect.h = srcRect.w = tileSize;
	srcRect.x = margin + tileID % cols * (tileSize + spacing);
	srcRect.y = margin + tileID / cols * (tileSize + spacing);
}

void Tileset::load()
{

}


