#include "DamageableEnemyComponent.h"
#include "GameObject.h"
#include "Enemy.h"


DamageableEnemyComponent::DamageableEnemyComponent(Enemy* o, MainCharacter* mc, float invincibleTime) : UpdateComponent(o)
{
	enemy = o;
	this->mc = mc;
	damageTimer = new Timer();
	this->invincibleTime = invincibleTime;
	attackedTimer = new Timer();
}


DamageableEnemyComponent::~DamageableEnemyComponent()
{
	delete damageTimer;
	delete attackedTimer;
}

void DamageableEnemyComponent::receiveMessage(Message* msg)
{
	if (msg->id == MC_ATTACK_DAMAGE) {
		if (enemy->isStunned()) {
			Message msg(STUN_OFF);
			enemy->sendMessage(&msg);
			enemy->setStun(false);
		}
		receiveDamage(MCAttackType::NORMAL, static_cast<MCAttackDamage*>(msg)->damage);
		attacked = true;
	}

	if (msg->id == MC_BULLET_COLLISION) {
		receiveDamage(MCAttackType::SHOT, static_cast<MCBulletStun*>(msg)->damage);
		attacked = true;
	}

	else if (msg->id == ULTIMATE) {
		timerOn=true;
		damage = static_cast<MCAttackDamage*>(msg)->damage;
		damageTimer->restart();
		if (enemy->isStunned()) {
			Message msg(STUN_OFF);
			enemy->sendMessage(&msg);
			enemy->setStun(false);
		}
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
			attacked = true;
		}
	}
	if (attacked) {//Solo entra cuando el personaje es invencible
		gameObject->setInvincibility(true);
		attackedTimer->update();//Activa el contador, y cuando pasa el tiempo límite lo vuelve vulnerable
		if (attackedTimer->TimeSinceTimerCreation > invincibleTime) {
			gameObject->setInvincibility(false);
			attackedTimer->restart();
			attacked = false;
		}
	}
	else {
		gameObject->setInvincibility(false);
		attackedTimer->restart();
	}
}

void DamageableEnemyComponent::receiveDamage(MCAttackType attackType, float damage)
{	
	float dmg = damage;
	int life = enemy->getLife();
	life -= damage;
	enemy->setLife(life);
	if (life <= 0) {		
		enemy->death();
	}
	else {
		Message msg(HURT);
		gameObject->setInvincibility(true);
		gameObject->sendMessage(&msg);
	}
}
