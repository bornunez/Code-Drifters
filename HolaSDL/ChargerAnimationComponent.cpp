#include "ChargerAnimationComponent.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"
#include "EnemyCharger.h"

ChargerAnimationComponent::ChargerAnimationComponent(EnemyCharger* o, GameObject* target, std::map<const char*, Animation*> anim, float hTime, float delayTime) : RenderComponent(o)
{
	animations = anim;
	this->target = target;
	this->ec = o;
	hurtTimer = new Timer();
	chargeTimer = new Timer();
	attackDelay = delayTime;
	hurtTime = hTime;
	gameObject->changeCurrentAnimation("RUNLEFT");
	gameObject->getCurrentAnimation()->startAnimation();
}


ChargerAnimationComponent::~ChargerAnimationComponent()
{
}

void ChargerAnimationComponent::render()
{
	handleAnimation();
	gameObject->getCurrentAnimation()->runAnimation();
}

void ChargerAnimationComponent::receiveMessage(Message* msg)
{
	switch (msg->id) {
	case ENEMY_SPAWN:
		hurtTimer->restart();
		chargeTimer->restart();
	case RUN_LEFT:
		gameObject->changeCurrentAnimation("RUNLEFT");
		break;
	case RUN_RIGHT:
		gameObject->changeCurrentAnimation("RUNRIGHT");
		break;
	case RUN_TOP:
		gameObject->changeCurrentAnimation("RUNRIGHT");
		break;
	case RUN_BOT:
		gameObject->changeCurrentAnimation("RUNLEFT");
		break;

	case CHARGE_LEFT:
		gameObject->changeCurrentAnimation("CHARGELEFT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case CHARGE_RIGHT:
		gameObject->changeCurrentAnimation("CHARGERIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case CHARGE_TOP:
		gameObject->changeCurrentAnimation("CHARGETOP");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case CHARGE_BOT:
		gameObject->changeCurrentAnimation("CHARGEBOT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;

	case PRECHARGE_LEFT:
		gameObject->changeCurrentAnimation("PRECHARGELEFT");
		gameObject->getCurrentAnimation()->startAnimation();
		chargeTimer->restart();
		break;
	case PRECHARGE_RIGHT:
		gameObject->changeCurrentAnimation("PRECHARGERIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
		chargeTimer->restart();
		break;
	case PRECHARGE_TOP:
		gameObject->changeCurrentAnimation("PRECHARGERIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
		chargeTimer->restart();
		break;
	case PRECHARGE_BOT:
		gameObject->changeCurrentAnimation("PRECHARGELEFT");
		gameObject->getCurrentAnimation()->startAnimation();
		chargeTimer->restart();
		break;

	/*case HURT:
		gameObject->changeCurrentAnimation("HURT");
		gameObject->getCurrentAnimation()->startAnimation();
		hurtTimer->restart();
		ec->enemyState = EnemyState::Hurt;
		break;*/
	case ENEMY_DEATH:
		if (gameObject->getCurrentAnimation()->getName() == "StunRight") {
			gameObject->changeCurrentAnimation("DEATHRIGHT");
		}
		else gameObject->changeCurrentAnimation("DEATHLEFT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case STUN:
		if (gameObject->getCurrentAnimation()->getName() == "ChargeRight" 
			|| gameObject->getCurrentAnimation()->getName() == "ChargeTop") {
			gameObject->changeCurrentAnimation("STUNRIGHT");
		}
		else gameObject->changeCurrentAnimation("STUNLEFT");		
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	}
}

void ChargerAnimationComponent::handleAnimation()
{
	if (!gameObject->isDead() && !ec->isStunned()) {

		//CÁLCULO DEL ÁNGULO ENTRE EL TARGET Y EL ENEMIGO
		Vector2D displayCenterPos = gameObject->getDisplayCenterPos();
		float angle = (atan2(target->getDisplayCenterPos().getY() - displayCenterPos.getY(), target->getDisplayCenterPos().getX() - displayCenterPos.getX()));//Angulo entre el enemigo y el target, en grados
		angle = angle * 180 / M_PI;
		if (angle < 0)
			angle += 360;

		/*if (ec->enemyState == EnemyState::Hurt) {
			hurtTimer->update();
			if (hurtTimer->TimeSinceTimerCreation > hurtTime) {
				ec->enemyState = EnemyState::Run;
				gameObject->changeCurrentAnimation("RUN");
			}
		}*/

		if (ec->enemyState == EnemyState::Run) {
				//Animacion charge según ángulo
				if (angle > 45 && angle < 135) {
					Message msg(RUN_BOT);
					gameObject->sendMessage(&msg);
				}
				else if (angle > 135 && angle < 225) {
					Message msg(RUN_LEFT);
					gameObject->sendMessage(&msg);
				}
				else if (angle > 225 && angle < 315) {
					Message msg(RUN_TOP);
					gameObject->sendMessage(&msg);
				}
				else {
					Message msg(RUN_RIGHT);
					gameObject->sendMessage(&msg);
				}

			}
		else if (ec->enemyState == EnemyState::Charge) {
			chargeTimer->update();
			if (chargeTimer->TimeSinceTimerCreation > attackDelay) {
				ec->enemyState = EnemyState::Attack;
				//Animacion charge según ángulo
				if (angle > 45 && angle < 135) {
					Message msg(CHARGE_BOT);
					gameObject->sendMessage(&msg);
				}
				else if (angle > 135 && angle < 225) {
					Message msg(CHARGE_LEFT);
					gameObject->sendMessage(&msg);
				}
				else if (angle > 225 && angle < 315) {
					Message msg(CHARGE_TOP);
					gameObject->sendMessage(&msg);
				}
				else {
					Message msg(CHARGE_RIGHT);
					gameObject->sendMessage(&msg);
				}

			}

		}
	}

}
