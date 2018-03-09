#include "TileLayer.h"
#include "Camera.h"

TileLayer::TileLayer(Tileset * tileset,string name, int cols, int rows, int tileSize) :Layer(name), tileSet(tileset), cols(cols), rows(rows), tileSize(tileSize)
{
}

TileLayer::~TileLayer()
{
}

void TileLayer::update()
{
}

void TileLayer::render(Camera* camera)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int tileID = tileIDs[i][j];
			if (tileID > 0) {
				SDL_Rect destRect;
				destRect.h = destRect.w = tileSize * scale;
				destRect.x = j * destRect.w - camera->getTransform()->position.getX();
				destRect.y = i * destRect.w - camera->getTransform()->position.getY();

				SDL_Rect* srcRect = tileSet->getTileRect(tileID-1);
				tileSet->getTexture()->render(destRect, srcRect);
			}
		}
	}
}
