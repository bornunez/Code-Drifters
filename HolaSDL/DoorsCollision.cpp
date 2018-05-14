#include "DoorsCollision.h"
#include "Transform.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "Room.h"
#include "Map.h"
#include "CollisionHandler.h"


DoorsCollision::DoorsCollision(GameObject* o) : UpdateComponent(o)
{
}


DoorsCollision::~DoorsCollision()
{
}

void DoorsCollision::update()
{
	Transform* t = gameObject->getTransform();

	//Colisionamos
	Room* currRoom = LevelManager::getInstance()->getCurrentRoom();
	bool collision = false;
	vector<Door*> doors = currRoom->getMap()->getDoors();
	for (int i = 0;!collision && i < 4; i++) {
		if (doors[i] != nullptr) {
			if (CollisionHandler::RectCollide(t->body, doors[i]->getTrigger())) {
				//Colisiona con el trigger
				t->velocity.set(0, 0);
				LevelManager::getInstance()->changeRoom((Direction)i);
				collision = true;
			}
		}
	}
}
