#pragma once
#include "ChargerComponent.h"
#include "EnemyCharger.h"

ChargerComponent::ChargerComponent(GameObject* o, GameObject* target, float cDelay, float aDelay, float aTime, float velMultiplier) :
			ChaseComponent(o, target), ChargeComponent(o, target, aDelay, aTime, velMultiplier), UpdateComponent(o)
{

	chargeDelay = cDelay;
	attackDelay = aDelay;
	attackTime = aTime;
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
		if ((ec->enemyState != EnemyState::Charge && ec->enemyState != EnemyState::Attack) && timer->TimeSinceTimerCreation >= chargeDelay) {
			ec->enemyState = EnemyState::Charge;
			timer->restart();
			ChargeComponent::resetTimer();
		}
		else if ((ec->enemyState == EnemyState::Charge || ec->enemyState == EnemyState::Attack) && timer->TimeSinceTimerCreation >= attackDelay + attackTime + .1) {
			ec->enemyState = EnemyState::Run;
			timer->restart();
			Message msg(STALKER_RUN);
			ec->sendMessage(&msg);
		}

		if (ec->enemyState == EnemyState::Charge || ec->enemyState == EnemyState::Attack) {
			ChargeComponent::update();
		}
		else if (ec->enemyState == EnemyState::Run) {
			ChaseComponent::update();
		}

		ec->setInvincibility(true);
	}

	else { 
		ec->setInvincibility(false);
	}
}