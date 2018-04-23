#pragma once
#include "ChargerComponent.h"
#include "EnemyCharger.h"

ChargerComponent::ChargerComponent(GameObject* o, GameObject* target, float cDelay, float aDelay, float aTime, float velMultiplier) :
			ChaseComponent(o, target), ChargeComponent(o, target, aDelay, aTime, velMultiplier), UpdateComponent(o)
{

	chargeDelay = cDelay;
	attackDelay = aDelay;
	attackTime = aTime;
	targetObject = target;
	ec = static_cast<EnemyCharger*>(o);
	ec->enemyState = EnemyState::Run;
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
			
			Vector2D displayCenterPos = gameObject->getDisplayCenterPos();
			float angle = (atan2(targetObject->getDisplayCenterPos().getY() - displayCenterPos.getY(), targetObject->getDisplayCenterPos().getX() - displayCenterPos.getX()));//Angulo entre el enemigo y el target, en grados
			angle = angle * 180 / M_PI;
			if (angle < 0)
				angle += 360;
			//Animacion precharge según ángulo
			if (angle > 45 && angle < 135) {
				Message msg(PRECHARGE_BOT);
				gameObject->sendMessage(&msg);
			}
			else if (angle > 135 && angle < 225) {
				Message msg(PRECHARGE_LEFT);
				gameObject->sendMessage(&msg);
			}
			else if (angle > 225 && angle < 315) {
				Message msg(PRECHARGE_TOP);
				gameObject->sendMessage(&msg);
			}
			else {
				Message msg(PRECHARGE_RIGHT);
				gameObject->sendMessage(&msg);
			}

			ec->enemyState = EnemyState::Charge;
			timer->restart();
			ChargeComponent::resetTimer();
		}
		else if ((ec->enemyState == EnemyState::Charge || ec->enemyState == EnemyState::Attack) && timer->TimeSinceTimerCreation >= attackDelay + attackTime + .1) {
			ec->enemyState = EnemyState::Run;
			timer->restart();
			
		}

		if (ec->enemyState == EnemyState::Charge || ec->enemyState == EnemyState::Attack) {
			ChargeComponent::update();
		}
		else if (ec->enemyState == EnemyState::Run) {
			ChaseComponent::update();
		}
	}

	else { 
		ec->enemyState = EnemyState::Run;
		Message msg(STUN);
		gameObject->sendMessage(&msg);
		timer->restart();
	}
}