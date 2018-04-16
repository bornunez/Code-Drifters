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

void KnockbackComponent::update()
{
}
void KnockbackComponent::knockback(Vector2D direction)
{
	Transform* t = gameObject->getTransform();

	t->position.set(t->position + direction * force * Time::getInstance()->DeltaTime);
}
void KnockbackComponent::receiveMessage(Message* msg) {
	if (msg->id == KNOCK_BACK) {
		knockback(static_cast<KnockbackMessage*>(msg)->knockback);
	}
}

KnockbackComponent::~KnockbackComponent()
{
}

