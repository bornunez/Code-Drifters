#include "CollisionHandler.h"
#include "Transform.h"
#include "TileLayer.h"
#include "Game.h"
#include "GameObject.h"



bool CollisionHandler::Collide(Transform * A, Transform * B)
{
	return RectCollide(A->body, B->body);
}

bool CollisionHandler::Collide(GameObject * A, GameObject * B)
{
	return RectCollide(A->getTransform()->body, B->getTransform()->body);
}

bool CollisionHandler::Collide(Transform * A, TileLayer * tileLayer)
{
	return Collide(A->body, tileLayer);
}

bool CollisionHandler::Collide(SDL_Rect A, TileLayer * tileLayer)
{
	vector<vector<int>> idLayer = tileLayer->getTileIDs();
	int tileSize = tileLayer->getTileSize(); int scale = Game::getGame()->getScale();
	int tileScale = (tileSize * scale); //Cuanto ocupa un tile en el mundo real


	int bodyX, bodyY;
	int bodyW, bodyH;

	//Esto nos sirve para saber los tiles que abarca el cuerpo
	//Es una conversion de coordenadas de mundo a coordenadas de matriz
	bodyX = max(A.x / tileScale, 0);
	bodyY = max(A.y / tileScale, 0);
	bodyW = (A.x + A.w) / tileScale;
	bodyH = (A.y + A.h) / tileScale;
	//Ahora comprobaremos si hay algun tile colisionable entre los tiles de la capa
	for (int i = bodyY;i < min(bodyH + 1, (int)idLayer.size()); i++) {
		for (int j = bodyX;j < min(bodyW + 1, (int)idLayer[i].size()); j++) {
			if (idLayer[i][j] != 0) {
				return true;
			}
		}
	}
	return false;
}

vector<bool> CollisionHandler::Collide(std::vector<SDL_Rect> rects, TileLayer * tileLayer)
{
	vector<bool> collisions(rects.size(), false);
	vector<vector<int>> idLayer = tileLayer->getTileIDs();
	int tileSize = tileLayer->getTileSize(); int scale = Game::getGame()->getScale();


	int bodyX, bodyY; //Coordenadas del inicio del cuerpo en la matriz del mapa
	int bodyW, bodyH; //Tamaño del cuerpo en matriz de mapa
	int tileScale = (tileSize * scale); //Cuanto ocupa un tile en el mundo real

	int k = 0;
	for (SDL_Rect rect : rects) {
		//Esto nos sirve para saber los tiles que abarca el cuerpo
		//Es una conversion de coordenadas de mundo a coordenadas de matriz
		bodyX = max(rect.x / tileScale,0);
		bodyY = max(rect.y / tileScale,0);
		bodyW = (rect.x + rect.w) / tileScale;
		bodyH = (rect.y + rect.h) / tileScale;
		//Ahora comprobaremos si hay algun tile colisionable entre los tiles de la capa
		for (int i = bodyY; !collisions[k] && i < min(bodyH + 1 , (int)idLayer.size()); i++) {
			for (int j = bodyX; !collisions[k] && j < min(bodyW + 1 , (int)idLayer[i].size()); j++) {
				if (idLayer[i][j] != 0) {

					collisions[k] = true;
					
				}
			}
		}
		k++;
	}

	return collisions;
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
