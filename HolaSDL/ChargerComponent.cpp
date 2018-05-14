#pragma once
#include "ChargerComponent.h"
#include "EnemyCharger.h"

ChargerComponent::ChargerComponent(Enemy* o, GameObject* target, float cDelay, float aDelay, float aTime, float velMultiplier) :
			ChaseComponent(o, target, 75), ChargeComponent(o, target, aDelay, aTime, velMultiplier), UpdateComponent(o)
{

	chargeDelay = cDelay;
	attackDelay = aDelay;
	attackTime = aTime;
	targetObject = target;
	ec = o;
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
		ChargeComponent::startCharge();
		break;
	case ENEMY_SPAWN:
		timer->restart();
	}
}


void ChargerComponent::update()
{
	timer->update();

	if (!ec->isDead()) {
		if ((abs(targetObject->getTransform()->position.getX() - ec->getTransform()->position.getX()) +
			abs(targetObject->getTransform()->position.getY() - ec->getTransform()->position.getY())) <= 900 && !ec->isStunned()) {
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