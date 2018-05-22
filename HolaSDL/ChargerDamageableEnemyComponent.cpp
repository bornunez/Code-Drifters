#include "ChargerDamageableEnemyComponent.h"
#include "GameObject.h"
#include "Enemy.h"


ChargerDamageableEnemyComponent::ChargerDamageableEnemyComponent(Enemy* o, MainCharacter* mc, float invincibleTime) : UpdateComponent(o)
{
	enemy = o;
	this->mc = mc;

	damageTimer = new Timer();
	this->invincibleTime = invincibleTime;
	attackedTimer = new Timer();
}


ChargerDamageableEnemyComponent::~ChargerDamageableEnemyComponent()
{
}

void ChargerDamageableEnemyComponent::receiveMessage(Message* msg)
{
	if (msg->id == MC_ATTACK_DAMAGE) {
		if (enemy->isStunned()) {
			receiveDamage(static_cast<MCAttackDamage*>(msg)->damage);
		}
		attacked = true;
		gameObject->setInvincibility(true);
	}
	else if (msg->id == ULTIMATE) {
		timerOn = true;
		damage = static_cast<MCAttackDamage*>(msg)->damage;
		damageTimer->restart();
	}
	else if (MC_BULLET_COLLISION) {
		receiveDamage(static_cast<MCBulletStun*>(msg)->damage);
	}
}

void ChargerDamageableEnemyComponent::update()
{
	if (timerOn) {
		damageTimer->update();
		if (damageTimer->TimeSinceTimerCreation > 1) {//El timer es para cuadrar la animación con el ataque
			damageTimer->restart();
			timerOn = false;
			receiveDamage(damage);
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


void ChargerDamageableEnemyComponent::receiveDamage(float damage)
{	
	float dmg = damage;//El daño se calcula restando el ataque del jugador con la defensa del enemigo
	int life = enemy->getLife();
	life -= damage;
	enemy->setLife(life);
	if (life <= 0) {
		enemy->death();
	}
	else {
		Message msg(HURT);
	
		gameObject->sendMessage(&msg);	
	}
	
}