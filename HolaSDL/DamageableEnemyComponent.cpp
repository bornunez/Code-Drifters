#include "DamageableEnemyComponent.h"
#include "GameObject.h"
#include "Enemy.h"
#include "MainCharacter.h"

DamageableEnemyComponent::DamageableEnemyComponent(Enemy* o, GameObject* mc) : UpdateComponent(o)
{
	enemy = o;
	this->mc = static_cast<MainCharacter*>(mc);
}


DamageableEnemyComponent::~DamageableEnemyComponent()
{
}

void DamageableEnemyComponent::recieveMessage(std::string msg) {
	if (msg == "NORMAL_ATTACK") {
		receiveDamage("NORMAL_ATTACK");
		gameObject->setInvincibility(true);
	}
}

void DamageableEnemyComponent::receiveDamage(std::string attackType)
{	
	float damage = mc->getAttackDamage(attackType) - enemy->getDefense();//El daño se calcula restando el ataque del jugador con la defensa del enemigo
	int life = enemy->getLife();
	life -= damage;
	enemy->setLife(life);
	if (life <= 0) {
		enemy->onDestroy();
	}
}
