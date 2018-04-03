#pragma once
#include "StalkerComponent.h"
#include "EnemyStalker.h"

StalkerComponent::StalkerComponent(GameObject * o, GameObject * target, float delay, float time, float velMultiplier) : ChaseComponent(o, target),
									ChargeComponent(o, target, delay, time, velMultiplier), UpdateComponent(o)
{
	timer = new Timer();
}

StalkerComponent::~StalkerComponent()
{
}

void StalkerComponent::update()
{
	timer->update();

	EnemyStalker* mc = static_cast<EnemyStalker*>(gameObject);

	if (timer->TimeSinceTimerCreation >= 8.0) {
		charge = !charge;
		timer->restart();
		if (charge) {
			mc->sendMessage("ATTACK");
			ChargeComponent::resetTimer();		//Reset del timer para que no se lance antes de cargar
		}
		else 
			mc->sendMessage("RUN");
	}

	if (!charge)
		ChaseComponent::update();
	else
		ChargeComponent::update();
}
