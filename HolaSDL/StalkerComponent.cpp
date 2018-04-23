#pragma once
#include "StalkerComponent.h"
#include "EnemyStalker.h"

StalkerComponent::StalkerComponent(GameObject * o, GameObject * target, float cDelay, float aDelay, float aTime, float velMultiplier) : ChaseComponent(o, target),
ChargeComponent(o, target, aDelay, aTime, velMultiplier), UpdateComponent(o)
{
	timer = new Timer();
	chargeDelay = cDelay;
	attackDelay = aDelay;
	attackTime = aTime;
	es = static_cast<EnemyStalker*>(gameObject);
	es->enemyState = EnemyState::Run;
}

StalkerComponent::~StalkerComponent()
{
}

void StalkerComponent::update()
{
	if (!gameObject->isDead()) {
		timer->update();

		;

		if (!es->isStunned()) {
			if ((es->enemyState != EnemyState::Charge && es->enemyState != EnemyState::Attack) && timer->TimeSinceTimerCreation >= chargeDelay) {
				es->enemyState = EnemyState::Charge;
				ChargeComponent::startCharge();
				timer->restart();
				Message msg(STALKER_CHARGE);
				es->sendMessage(&msg);
			}
			else if ((es->enemyState == EnemyState::Charge || es->enemyState == EnemyState::Attack) && timer->TimeSinceTimerCreation >= attackDelay + attackTime + .1) {
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

			if (es->enemyState == EnemyState::Charge || es->enemyState == EnemyState::Attack)
				ChargeComponent::update();

			else if (es->enemyState == EnemyState::Run)
				ChaseComponent::update();
		}
		else {
			gameObject->getTransform()->velocity.set({ 0,0 });
		}
	}
}
