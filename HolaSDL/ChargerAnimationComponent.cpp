#include "ChargerAnimationComponent.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"
#include "EnemyCharger.h"

ChargerAnimationComponent::ChargerAnimationComponent(EnemyCharger* o, GameObject* target, std::map<const char*, Animation*> anim, float hTime, float delayTime) : RenderComponent(o)
{
	animations = anim;
	gameObject->changeCurrentAnimation("RUN");
	this->target = target;
	this->es = o;
	hurtTimer = new Timer();
	chargeTimer = new Timer();
	attackDelay = delayTime;
	hurtTime = hTime;

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
	case RUN_LEFT:
		gameObject->changeCurrentAnimation("RUNLEFT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case RUN_RIGHT:
		gameObject->changeCurrentAnimation("RUNRIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case RUN_TOP:
		gameObject->changeCurrentAnimation("RUNTOP");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case RUN_BOT:
		gameObject->changeCurrentAnimation("RUNBOT");
		gameObject->getCurrentAnimation()->startAnimation();
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
		break;
	case PRECHARGE_RIGHT:
		gameObject->changeCurrentAnimation("PRECHARGERIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case PRECHARGE_TOP:
		gameObject->changeCurrentAnimation("PRECHARGETOP");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case PRECHARGE_BOT:
		gameObject->changeCurrentAnimation("PRECHARGEBOT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;

	case HURT:
		gameObject->changeCurrentAnimation("HURT");
		gameObject->getCurrentAnimation()->startAnimation();
		hurtTimer->restart();
		es->enemyState = EnemyState::Hurt;
		break;
	case ENEMY_DEATH:
		gameObject->changeCurrentAnimation("DEATH");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	}
}

void ChargerAnimationComponent::handleAnimation()
{
	if (!gameObject->isDead()) {

		//CÁLCULO DEL ÁNGULO ENTRE EL TARGET Y EL ENEMIGO
		Vector2D displayCenterPos = gameObject->getDisplayCenterPos();
		float angle = (atan2(target->getDisplayCenterPos().getY() - displayCenterPos.getY(), target->getDisplayCenterPos().getX() - displayCenterPos.getX()));//Angulo entre el enemigo y el target, en grados
		angle = angle * 180 / M_PI;
		if (angle < 0)
			angle += 360;

		if (es->enemyState == EnemyState::Hurt) {
			hurtTimer->update();
			if (hurtTimer->TimeSinceTimerCreation > hurtTime) {
				es->enemyState = EnemyState::Run;
				gameObject->changeCurrentAnimation("RUN");
			}
		}


		else if (es->enemyState == EnemyState::Charge) {
			chargeTimer->update();
			if (chargeTimer->TimeSinceTimerCreation > attackDelay) {
				es->enemyState = EnemyState::Attack;
				Message msg(STALKER_ATTACK);
				es->sendMessage(&msg);

			}
		}
	}
}
