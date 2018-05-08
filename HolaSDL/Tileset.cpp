#include "Tileset.h"



Tileset::Tileset(Texture* tileImg, XMLElement* root) : tilesetImg(tileImg)
{
	name = root->Attribute("name");
	tileSize = atoi( root->Attribute("tilewidth"));
	if (root->Attribute("spacing"))
		spacing = atoi(root->Attribute("spacing"));
	else
		spacing = 0;
	if(root->Attribute("margin"))
		margin = atoi(root->Attribute("margin"));
	else
		margin = 0;
	tileCount = atoi(root->Attribute("tilecount"));
	cols = atoi(root->Attribute("columns"));
	rows = tileCount / cols;

	for (int i = 0; i < rows*cols; i++) {
		tileRects.push_back(setTileRect(i));
	}
}

SDL_Rect Tileset::setTileRect(int tileID)
{
	SDL_Rect srcRect;
	srcRect.h = srcRect.w = tileSize;
	srcRect.x = margin + tileID % cols * (tileSize + spacing);
	srcRect.y = margin + tileID / cols * (tileSize + spacing);
	return srcRect;
}

SDL_Rect * Tileset::getTileRect(int tileID)
{
	return &tileRects.at(tileID);
}

void Tileset::load()
{

}


