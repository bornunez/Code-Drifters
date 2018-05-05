#include "DamageableEnemyComponent.h"
#include "GameObject.h"
#include "Enemy.h"


DamageableEnemyComponent::DamageableEnemyComponent(Enemy* o, GameObject* mc) : UpdateComponent(o)
{
	enemy = o;
	this->mc = static_cast<MainCharacter*>(mc);
	damageTimer = new Timer();
}


DamageableEnemyComponent::~DamageableEnemyComponent()
{
}

void DamageableEnemyComponent::receiveMessage(Message* msg)
{
	if (msg->id == MC_ATTACK_DAMAGE) {
		receiveDamage(MCAttackType::NORMAL, static_cast<MCAttackDamage*>(msg)->damage);		
	}
	else if (msg->id == ULTIMATE) {
		timerOn=true;
		damage = static_cast<MCAttackDamage*>(msg)->damage;
		damageTimer->restart();
	}
}

void DamageableEnemyComponent::update()
{
	if (timerOn) {
		damageTimer->update();
		if (damageTimer->TimeSinceTimerCreation > 1) {//El timer es para cuadrar la animación con el ataque
			damageTimer->restart();
			timerOn = false;
			receiveDamage(MCAttackType::NORMAL, damage);
		}
	}
}

void DamageableEnemyComponent::receiveDamage(MCAttackType attackType, float damage)
{	
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
