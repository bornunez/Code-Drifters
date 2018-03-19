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

void DamageableEnemyComponent::receiveMessage(std::string msg) {
	if (msg == "NORMAL_ATTACK") {
		enemy->receiveDamage("NORMAL_ATTACK");
		enemy->setInvincibility(true);
	}
}
