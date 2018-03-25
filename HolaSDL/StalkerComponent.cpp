#pragma once
#include "StalkerComponent.h"





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

	if (timer->TimeSinceTimerCreation >= 8.0) {
		charge = !charge;
		timer->restart();
	}

	if (!charge)
		ChaseComponent::update();
	else
		ChargeComponent::update();
}
