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
	if (!gameObject->isDead()) {
		timer->update();

		EnemyStalker* es = static_cast<EnemyStalker*>(gameObject);

		if (!es->isStunned()) {
			if (es->enemyState != EnemyState::Charge && timer->TimeSinceTimerCreation >= 8.0) {
				es->enemyState = EnemyState::Charge;
				timer->restart();
				Message msg(STALKER_ATTACK);
				es->sendMessage(&msg);
				ChargeComponent::resetTimer();
			}
			else if (es->enemyState == EnemyState::Charge && timer->TimeSinceTimerCreation >= 3.0) {
				es->enemyState = EnemyState::Run;
				timer->restart();
				Message msg(STALKER_RUN);
				es->sendMessage(&msg);

			}





			//if (timer->TimeSinceTimerCreation >= 8.0) {
			//	charge = !charge;
			//	timer->restart();
			//	if (charge) {
			//		mc->sendMessage("ATTACK");
			//		ChargeComponent::resetTimer();		//Reset del timer para que no se lance antes de cargar
			//	}
			//	else 
			//		mc->sendMessage("RUN");
			//}

			if (es->enemyState == EnemyState::Charge)
				ChargeComponent::update();

			else
				ChaseComponent::update();
		}
		else {
			gameObject->getTransform()->velocity.set({ 0,0 });
		}
	}
}
