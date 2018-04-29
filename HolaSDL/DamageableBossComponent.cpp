#include "DamageableBossComponent.h"
#include "GameObject.h"
#include "MainCharacter.h"

DamageableBossComponent::DamageableBossComponent(MasterBoss* o, GameObject* mc) : UpdateComponent(static_cast<GameObject*>(o))
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
	float dmg = damage - boss->getDefense();//El daño se calcula restando el ataque del jugador con la defensa del enemigo
	int life = boss->getLife();
	life -= damage;
	boss->setLife(life);
	//Los numeros aqui no valen pa na
	boss->changeColor(0, 0, 0);
	cout << boss->getLife();
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
