#include "DamageableBossComponent.h"
#include "GameObject.h"
#include "MainCharacter.h"

DamageableBossComponent::DamageableBossComponent(MasterBoss* o, MainCharacter* mc, float invincibleTime) : UpdateComponent(static_cast<GameObject*>(o))
{
	boss = o;
	this->mc = mc;
	damageTimer = new Timer();
	this->invincibleTime = invincibleTime;
	attackedTimer = new Timer();
}


DamageableBossComponent::~DamageableBossComponent()
{
	delete damageTimer;
	delete attackedTimer;
}

void DamageableBossComponent::receiveMessage(Message* msg)
{
	switch (msg->id) {
	case MC_ATTACK_DAMAGE:
		receiveDamage(static_cast<MCAttackDamage*>(msg)->damage);
		attacked = true;
		gameObject->setInvincibility(true);
		break;

	case MC_BULLET_COLLISION:
		receiveDamage(static_cast<MCBulletStun*>(msg)->damage);
		break;

	case ULTIMATE:
		timerOn = true;
		damage = static_cast<MCAttackDamage*>(msg)->damage;
		damageTimer->restart();
		break;
	}
}


void DamageableBossComponent::update()
{
	if (timerOn) {
		damageTimer->update();
		if (damageTimer->TimeSinceTimerCreation > 1) {//El timer es para cuadrar la animaci�n con el ataque
			damageTimer->restart();
			timerOn = false;
			receiveDamage(damage);
			attacked = true;
		}
	}
	if (attacked) {//Solo entra cuando el personaje es invencible
		gameObject->setInvincibility(true);
		attackedTimer->update();//Activa el contador, y cuando pasa el tiempo l�mite lo vuelve vulnerable
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

void DamageableBossComponent::receiveDamage(float damage)
{
	float dmg = damage;//El da�o se calcula restando el ataque del jugador con la defensa del enemigo
	int life = boss->getLife();
	life -= damage;
	boss->setLife(life);
	//Los numeros aqui no valen pa na
	boss->changeColor(0, 0, 0);
	if (life <= 0) {
		boss->death();
	}
	else {
		Message msg(HURT);		
		gameObject->sendMessage(&msg);
	}
}
