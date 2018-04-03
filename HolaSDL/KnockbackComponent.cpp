#include "KnockbackComponent.h"
#include "GameObject.h"
#include "Time.h"
#include <vector>
#include "Room.h"
#include "LevelManager.h"
#include "CollisionHandler.h"
#include "Room.h"
#include "PlayState.h"
#include "TileLayer.h"
#include "Map.h"
#include "Time.h"
#include "Managers.h"
#include <string>
using namespace std;
KnockbackComponent::KnockbackComponent(GameObject* o, int knockbackForce): UpdateComponent(o)
{
	force = knockbackForce;
}
KnockbackComponent::KnockbackComponent(GameObject * o, int knockbackForce, string layer) : UpdateComponent(o)
{
	force = knockbackForce;
	collisionsLayer.push_back(layer);
}

KnockbackComponent::KnockbackComponent(GameObject * o, int knockbackForce, vector<string> collisionsL) : UpdateComponent(o)
{
	force = knockbackForce;
	collisionsLayer = collisionsL;
}

void KnockbackComponent::update()
{
}
void KnockbackComponent::knockback(Vector2D direction)
{
	Transform* t = gameObject->getTransform();
	Transform auxT = *t;

	auxT.position.setX(auxT.position.getX() + direction.getX() * force * (Time::getInstance()->DeltaTime));
	auxT.position.setY(auxT.position.getY() + direction.getY() * force * (Time::getInstance()->DeltaTime));
	auxT.body.x = auxT.position.getX(); auxT.body.y = auxT.position.getY();
	//Colisionamos
	Room* currRoom = LevelManager::getInstance()->getCurrentRoom();
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
	if (!collision)
		*t = auxT;
}
void KnockbackComponent::receiveMessage(Message* msg) {
	if (msg->id == KNOCK_BACK) {
		knockback(static_cast<KnockbackMessage*>(msg)->knockback);
	}
}

KnockbackComponent::~KnockbackComponent()
{
}

