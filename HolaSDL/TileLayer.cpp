#include "TileLayer.h"

TileLayer::TileLayer(Tileset * tileset,string name, int cols, int rows, int tileSize) : tileSet(tileset),name(name), cols(cols), rows(rows), tileSize(tileSize)
{
}

TileLayer::~TileLayer()
{
}

void TileLayer::update()
{
}

void TileLayer::render()
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int tileID = tileIDs[i][j];
			if (tileID > 0) {
				SDL_Rect destRect;
				destRect.h = destRect.w = tileSize * 3;
				destRect.x = j * destRect.w;
				destRect.y = i * destRect.w;

				SDL_Rect* srcRect = tileSet->getTileRect(tileID-1);
				tileSet->getTexture()->render(destRect, srcRect);
			}
		}
	}
}
