#include "BasicMovement.h"
#include "GameObject.h"
#include "Transform.h"
#include "CollisionHandler.h"
#include "Room.h"
#include "PlayState.h"
#include "TileLayer.h"
#include "Map.h"
#include "Time.h"


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
	Transform* t = gameObject->getTransform();

	Transform auxT = *t;

	//Movemos al personaje y a su body
	//cout << "DeltaTime: [ " << Time::getInstance()->DeltaTime << " ]" << endl;
	auxT.position.set(auxT.position + auxT.velocity * auxT.speed * (Time::getInstance()->DeltaTime));
	auxT.body.x = auxT.position.getX(); auxT.body.y = auxT.position.getY();

	//Colisionamos
	Room* currRoom = PlayState::getInstance()->getCurrentRoom();
	bool collision = false;
	vector<string>::iterator it;
	for (it = collisionsLayer.begin(); it != collisionsLayer.end() && !collision; it++) {
		TileLayer* tl = static_cast<TileLayer*>(currRoom->getMap()->GetLayer(*it));
		if (tl != nullptr) {
			if (CollisionHandler::Collide(&auxT, tl)) {
				t->velocity.set(0, 0);
				collision = true;
			}
		}
	}
	if(!collision)
		*t = auxT;

}
