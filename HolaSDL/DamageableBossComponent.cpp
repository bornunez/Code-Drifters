#include "DamageableBossComponent.h"
#include "GameObject.h"
#include "MainCharacter.h"

DamageableBossComponent::DamageableBossComponent(MasterBoss* o, GameObject* mc, float invincibleTime) : UpdateComponent(static_cast<GameObject*>(o))
{
	boss = o;
	this->mc = static_cast<MainCharacter*>(mc);
	damageTimer = new Timer();
	this->invincibleTime = invincibleTime;
	attackedTimer = new Timer();
}


DamageableBossComponent::~DamageableBossComponent()
{
}

void DamageableBossComponent::receiveMessage(Message* msg)
{
	if (msg->id == MC_ATTACK_DAMAGE) {
		receiveDamage(MCAttackType::NORMAL, static_cast<MCAttackDamage*>(msg)->damage);
		attacked = true;
	}
	else if (msg->id == ULTIMATE) {
		timerOn = true;
		damage = static_cast<MCAttackDamage*>(msg)->damage;
		damageTimer->restart();
	}
}

void DamageableBossComponent::update()
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

void DamageableBossComponent::receiveDamage(MCAttackType attackType, float damage)
{
	float dmg = damage;//El daño se calcula restando el ataque del jugador con la defensa del enemigo
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
		gameObject->setInvincibility(true);
		gameObject->sendMessage(&msg);
	}
}
