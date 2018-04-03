#pragma once
#include "ChargerComponent.h"
#include "EnemyCharger.h"

ChargerComponent::ChargerComponent(GameObject* o, GameObject* target, float delay, float time, float velMultiplier) : 
			ChaseComponent(o, target), ChargeComponent(o, target, delay, time, velMultiplier), UpdateComponent(o)
{
	timer = new Timer();
}

ChargerComponent::~ChargerComponent()
{
}

void ChargerComponent::update()
{
	timer->update();

	EnemyCharger* ec = static_cast<EnemyCharger*>(gameObject);
	
	
	if (!charge && timer->TimeSinceTimerCreation >= 8.0) {
		charge = true;
		timer->restart();
		ec->sendMessage("ATTACK");
		ChargeComponent::resetTimer();
	}
	else if (charge && timer->TimeSinceTimerCreation >= 3.0) {
		charge = false;
		timer->restart();
		ec->sendMessage("RUN");
	}
	
	if (!charge) {
		ChaseComponent::update();
		ec->setInvincibility(true);
	}
	else {
		ec->setInvincibility(false);
		ChargeComponent::update();
		
	}
}
