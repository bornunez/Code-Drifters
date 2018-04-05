#include "TileLayer.h"
#include "Camera.h"
#include "Game.h"

TileLayer::TileLayer(vector<Tileset*> tileSets,string name, int cols, int rows, int tileSize) :Layer(name), tileSets(tileSets), cols(cols), rows(rows), tileSize(tileSize)
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
				//El rect de donde vamos a pintar el tile
				SDL_Rect destRect;
				destRect.h = destRect.w = tileSize * Game::getGame()->getScale();
				destRect.x = j * destRect.w - camera->getTransform()->position.getX();
				destRect.y = i * destRect.w - camera->getTransform()->position.getY();
				//Cogemos el tileset, que será el ultimo 
				int tileS = 0;
				while (tileS < tileSets.size() && (tileID - firstGids[tileS]) > tileSets[tileS]->getTileCount())
					tileS++;
				tileID -= firstGids[tileS];
				SDL_Rect* srcRect = tileSets[tileS]->getTileRect(tileID);
				tileSets[tileS]->getTexture()->render(destRect, srcRect);
			}
		}
	}
}
