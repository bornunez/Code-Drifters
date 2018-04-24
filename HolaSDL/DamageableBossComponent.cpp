#include "DamageableBossComponent.h"
#include "GameObject.h"
#include "Boss.h"
#include "MainCharacter.h"

DamageableBossComponent::DamageableBossComponent(Boss* o, GameObject* mc) : UpdateComponent(static_cast<GameObject*>(o))
{
	boss = o;
	this->mc = static_cast<MainCharacter*>(mc);
}


DamageableBossComponent::~DamageableBossComponent()
{
}

void DamageableBossComponent::receiveMessage(Message* msg)
{
	if (msg->id == MC_ATTACK_DAMAGE) {
		receiveDamage("NORMAL_ATTACK", static_cast<MCAttackDamage*>(msg)->damage);
	}
}

void DamageableBossComponent::receiveDamage(std::string attackType, float damage)
{
	float dmg = damage - boss->getDefense();//El da�o se calcula restando el ataque del jugador con la defensa del enemigo
	int life = boss->getLife();
	life -= damage;
	boss->setLife(life);
	cout << "da�o";
	if (life <= 0) {
		boss->death();
		//enemy->onDestroy();
	}
	else {
		gameObject->setInvincibility(true);
		Message msg(HURT);
		gameObject->sendMessage(&msg);
	}
}