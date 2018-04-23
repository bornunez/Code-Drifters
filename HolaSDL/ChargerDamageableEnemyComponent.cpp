#include "ChargerDamageableEnemyComponent.h"
#include "GameObject.h"
#include "Enemy.h"
#include "MainCharacter.h"

ChargerDamageableEnemyComponent::ChargerDamageableEnemyComponent(Enemy* o, GameObject* mc) : UpdateComponent(o)
{
	enemy = o;
	this->mc = static_cast<MainCharacter*>(mc);
}


ChargerDamageableEnemyComponent::~ChargerDamageableEnemyComponent()
{
}

void ChargerDamageableEnemyComponent::receiveMessage(Message* msg)
{
	if (msg->id == MC_ATTACK_DAMAGE) {
		receiveDamage("NORMAL_ATTACK", static_cast<MCAttackDamage*>(msg)->damage);		
	}
}

void ChargerDamageableEnemyComponent::receiveDamage(std::string attackType, float damage)
{
	if (enemy->isStunned()) {
		float dmg = damage - enemy->getDefense();//El daño se calcula restando el ataque del jugador con la defensa del enemigo
		int life = enemy->getLife();
		life -= damage;
		enemy->setLife(life);
		if (life <= 0) {
			enemy->death();
			//enemy->onDestroy();
		}
		else {
			gameObject->setInvincibility(true);
			Message msg(HURT);
			gameObject->sendMessage(&msg);
		}
	}
}