#include "DamageableEnemyComponent.h"
#include "GameObject.h"
#include "Enemy.h"


DamageableEnemyComponent::DamageableEnemyComponent(Enemy* o) : UpdateComponent(o)
{
	enemy = o;
}


DamageableEnemyComponent::~DamageableEnemyComponent()
{
}

void DamageableEnemyComponent::recieveMessage(std::string msg) {
	if (msg == "Damage") {
		enemy->receiveDamage(10);
	}
}
