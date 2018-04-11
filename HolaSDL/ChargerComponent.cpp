#pragma once
#include "ChargerComponent.h"
#include "EnemyCharger.h"

ChargerComponent::ChargerComponent(GameObject* o, GameObject* target, float delay, float time, float velMultiplier) : 
			ChaseComponent(o, target), ChargeComponent(o, target, delay, time, velMultiplier), UpdateComponent(o)
{
	ec = static_cast<EnemyCharger*>(o);
	timer = new Timer();
}

ChargerComponent::~ChargerComponent()
{
}



void ChargerComponent::update()
{
	timer->update();

	if (!ec->isStunned()) {
		if (ec->enemyState != EnemyState::Charge && timer->TimeSinceTimerCreation >= 3.0) {
			ec->enemyState = EnemyState::Charge;
			timer->restart();
			Message msg(STALKER_ATTACK);
			ec->sendMessage(&msg);
			ChargeComponent::resetTimer();
		}
		else if (ec->enemyState == EnemyState::Charge && timer->TimeSinceTimerCreation >= 3.0) {
			ec->enemyState = EnemyState::Run;
			timer->restart();
			Message msg(STALKER_RUN);
			ec->sendMessage(&msg);
		}

		if (ec->enemyState == EnemyState::Charge) {
			ChargeComponent::update();
		}
		else {
			ChaseComponent::update();
		}

		ec->setInvincibility(true);
	}

	else { 
		ec->setInvincibility(false);
	}
}