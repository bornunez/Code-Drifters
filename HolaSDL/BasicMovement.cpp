#include "BasicMovement.h"
#include "GameObject.h"
#include "Transform.h"
#include "CollisionHandler.h"
#include "Room.h"
#include "PlayState.h"
#include "TileLayer.h"
#include "Map.h"
#include "Time.h"
#include "Managers.h"


BasicMovement::BasicMovement(GameObject * o) : UpdateComponent(o)
{
}

BasicMovement::BasicMovement(GameObject * o, string layer) : UpdateComponent(o)
{
	collisionsLayer.push_back(layer);
}

BasicMovement::BasicMovement(GameObject * o, vector<string> collisionsL) : UpdateComponent(o)
{
	collisionsLayer = collisionsL;
}


BasicMovement::~BasicMovement()
{
}

void BasicMovement::update()
{
	if (gameObject->canMove()) {
		Transform* t = gameObject->getTransform();

		Transform auxTx = *t;
		Transform auxTy = *t;
		//Movemos al personaje y a su body
		//cout << "DeltaTime: [ " << Time::getInstance()->DeltaTime << " ]" << endl;
		auxTx.position.setX(auxTx.position.getX() + auxTx.velocity.getX() * auxTx.speed * (min((float)1, Time::getInstance()->DeltaTime)));
		auxTy.position.setY(auxTy.position.getY() + auxTy.velocity.getY() * auxTy.speed * (min((float)1, Time::getInstance()->DeltaTime)));
		auxTx.body.x = auxTx.position.getX(); auxTx.body.y = auxTx.position.getY();
		auxTy.body.x = auxTy.position.getX(); auxTy.body.y = auxTy.position.getY();
		vector<SDL_Rect> rects = { auxTx.body, auxTy.body };
		vector<bool> collisions = { false,false };
		//Colisionamos
		Room* currRoom = LevelManager::getInstance()->getCurrentRoom();
		bool collisionX = false;
		bool collisionY = false;
		vector<string>::iterator it;
		for (it = collisionsLayer.begin(); it != collisionsLayer.end() && (!collisionX || !collisionY); it++) {
			TileLayer* tl = static_cast<TileLayer*>(currRoom->getMap()->GetLayer(*it));
			if (tl != nullptr) {
				collisions = CollisionHandler::Collide(rects, tl);
				collisionX = collisions[0] || collisionX;
				collisionY = collisions[1] || collisionY;
			}
		}
		//Si no hay colision nos movemos donde podamos
		if (!collisionX) {
			t->position.setX(auxTx.position.getX());
			t->body.x = auxTx.position.getX();
		}
		if (!collisionY) {
			t->position.setY(auxTy.position.getY());
			t->body.y = auxTy.position.getY();
		}
		//Si hay colision lo notificamos
		if (collisionX || collisionY) {
			Message msg(HIT_WALL);
			gameObject->sendMessage(&msg);
		}
	}
}
