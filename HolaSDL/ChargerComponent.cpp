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
void ChargerComponent::receiveMessage(Message * msg)
{
	switch (msg->id) {
	case HIT_WALL:
		if (ec->getEnemyState() == EnemyState::Hooked) {//Si está siendo enganchado y choca con la pared, se desengancha
			static_cast<MainCharacter*>(targetObject)->getHook().setHookStatus(HookStatus::STOP);
			Message msg(HOOK_STOP);
			static_cast<MainCharacter*>(targetObject)->sendMessage(&msg);
			ec->getEnemyState() == EnemyState::Idle;
			static_cast<MainCharacter*>(targetObject)->setMCState(MCState::Idle);

		}
		break;
	}
}


void ChargerComponent::update()
{
	timer->update();

	if (!ec->isDead()) {
		if (!ec->isStunned()) {
			ec->setMovable(true);
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
				ChargeComponent::startCharge();
				timer->restart();
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
			gameObject->getTransform()->velocity.set({ 0,0 });
			ec->setMovable(false);
			ec->enemyState = EnemyState::Run;
			Message msg(STUN);
			gameObject->sendMessage(&msg);
			timer->restart();
		}
	}
}