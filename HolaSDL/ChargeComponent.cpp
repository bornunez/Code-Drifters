#pragma once
#include "ChargeComponent.h"
#include "GameObject.h"
#include "Time.h"


ChargeComponent::ChargeComponent(GameObject* o, float delay, float time, float velMultiplier) : UpdateComponent(o)
{

	chargeDelay = delay;
	chargeTime = time;
	velocityMult = velMultiplier;
	timer = new Timer();

}


ChargeComponent::~ChargeComponent()
{
}

void ChargeComponent::update() {
	
	if (!charging) {
		if (timer->TimeSinceTimerCreation > chargeDelay)
		{
			charging = true;
			timer->restart();
		}
		timer->update();
	}

	else {
		if (timer->TimeSinceTimerCreation < chargeTime) {
			Transform* chaserT = gameObject->getTransform();
			chaserT->position.set(chaserT->position + chaserT->velocity * chaserT->speed *
				velocityMult * (Time::getInstance()->DeltaTime));
			timer->update();
		}
		else {
			timer->restart();
			charging = false;
		}
	}
	

}