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

		t->position.set(t->position + t->velocity * t->speed * Time::getInstance()->DeltaTime) ;
		t->body.x = t->position.getX(); t->body.y = t->position.getY();
	}
}
