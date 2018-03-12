#include "CollisionHandler.h"
#include "Transform.h"
#include "TileLayer.h"
#include <vector>

using namespace std;

bool CollisionHandler::Collide(Transform * A, Transform * B)
{
	if (RectCollide(A->body, B->body)) {
		A->velocity.set(0, 0);
		B->velocity.set(0, 0);
	}

	return false;
}

bool CollisionHandler::Collide(Transform * A, TileLayer * tileLayer)
{
	return -Collide(A->body, tileLayer);
}

bool CollisionHandler::Collide(SDL_Rect A, TileLayer * tileLayer)
{
	vector<vector<int>> idLayer = tileLayer->getTileIDs();
	int tileSize = tileLayer->getTileSize(); int scale = tileLayer->getScale();

	for (int i = 0; i < idLayer.size(); i++) {
		for (int j = 0; j < idLayer[i].size(); j++) {
			if (idLayer[i][j] != 0) {
				//El rect del bloque, con coordenadas de mundo real
				SDL_Rect destRect;
				destRect.h = destRect.w = tileSize * scale;
				destRect.x = j * destRect.w;
				destRect.y = i * destRect.w;
				//Vemos si colisiona el prota con el bloque
				if (RectCollide(A, destRect)) {
					return true;
				}
			}
		}
	}
	return false;
}

CollisionHandler::CollisionHandler()
{
}

int CollisionHandler::RectCollide(SDL_Rect a, SDL_Rect b)
{
	if (b.x + b.w < a.x)	return 0;	/*Just checking if their*/
	if (b.x > a.x + a.w)	return 0;	/*Bounding boxes even touch*/
										/*Write down on paper if*/
	if (b.y + b.h < a.y)	return 0;	/*Don't make sense*/
	if (b.y > a.y + a.h)	return 0;

	return 1;				/*Bouding boxes intersect*/
}

CollisionHandler::~CollisionHandler()
{
}
