#include "GunnerAnimationComponent.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"
#include "MainCharacter.h"
#include "EnemyGunner.h"
GunnerAnimationComponent::GunnerAnimationComponent(GameObject* o, GameObject* target,std::map<const char*, Animation*> anim) : RenderComponent(o)
{
	animations = anim;
	this->target = target;
	gameObject->changeCurrentAnimation("IDLE_BOT");
}


GunnerAnimationComponent::~GunnerAnimationComponent()
{
}

void GunnerAnimationComponent::render()
{
	handleAnimations();
	gameObject->getCurrentAnimation()->runAnimation();

}

void GunnerAnimationComponent::receiveMessage(std::string msg)
{
	if (msg == "RUN_LEFT") {
		gameObject->changeCurrentAnimation("RUN_LEFT");
	}
	else if (msg == "RUN_RIGHT") {
		gameObject->changeCurrentAnimation("RUN_RIGHT");
	}
	else if (msg == "RUN_TOP") {
		gameObject->changeCurrentAnimation("RUN_TOP");
	}
	else if (msg == "RUN_BOT") {
		gameObject->changeCurrentAnimation("RUN_BOT");
	}
	else if (msg == "IDLE_LEFT") {
		gameObject->changeCurrentAnimation("IDLE_LEFT");
	}
	else if (msg == "IDLE_RIGHT") {
		gameObject->changeCurrentAnimation("IDLE_RIGHT");
	}
	else if (msg == "IDLE_TOP") {
		gameObject->changeCurrentAnimation("IDLE_TOP");
	}
	else if (msg == "IDLE_BOT") {
		gameObject->changeCurrentAnimation("IDLE_BOT");
	}
	else if (msg == "IDLE_TOPLEFT") {
		gameObject->changeCurrentAnimation("IDLE_TOPLEFT");
	}
	else if (msg == "IDLE_BOTLEFT") {
		gameObject->changeCurrentAnimation("IDLE_BOTLEFT");
	}
	else if (msg == "IDLE_TOPRIGHT") {
		gameObject->changeCurrentAnimation("IDLE_TOPRIGHT");
	}
	else if (msg == "IDLE_BOTRIGHT") {
		gameObject->changeCurrentAnimation("IDLE_BOTRIGHT");
	}
	else if (msg == "SHOT_LEFT") {
		gameObject->changeCurrentAnimation("SHOT_LEFT");
		gameObject->getCurrentAnimation()->startAnimation();
	}
	else if (msg == "SHOT_RIGHT") {
		gameObject->changeCurrentAnimation("SHOT_RIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
	}
	else if (msg == "SHOT_TOP") {
		gameObject->changeCurrentAnimation("SHOT_TOP");
		gameObject->getCurrentAnimation()->startAnimation();
	}
	else if (msg == "SHOT_BOT") {
		gameObject->changeCurrentAnimation("SHOT_BOT");
		gameObject->getCurrentAnimation()->startAnimation();
	}
	else if (msg == "SHOT_TOPLEFT") {
		gameObject->changeCurrentAnimation("SHOT_TOPLEFT");
		gameObject->getCurrentAnimation()->startAnimation();
	}
	else if (msg == "SHOT_BOTLEFT") {
		gameObject->changeCurrentAnimation("SHOT_BOTLEFT");
		gameObject->getCurrentAnimation()->startAnimation();
	}
	else if (msg == "SHOT_TOPRIGHT") {
		gameObject->changeCurrentAnimation("SHOT_TOPRIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
	}
	else if (msg == "SHOT_BOTRIGHT") {
		gameObject->changeCurrentAnimation("SHOT_BOTRIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
	}
}

void GunnerAnimationComponent::handleAnimations()
{
	EnemyGunner* eg = static_cast<EnemyGunner*>(gameObject);
	Transform* gunnerT = gameObject->getTransform();
	if (eg->currentState != SHOOT) {
		if (gunnerT->velocity.getX() != 0 && gunnerT->velocity.getY() != 0) {
			eg->currentState = RUN;
		}
		else {
			eg->currentState = IDLE;
		}
	}
	

	//CÁLCULO DEL ÁNGULO ENTRE EL TARGET Y EL ENEMIGO
	Vector2D displayCenterPos = gameObject->getDisplayCenterPos();
	float angle = (atan2(target->getDisplayCenterPos().getY() - displayCenterPos.getY(), target->getDisplayCenterPos().getX() - displayCenterPos.getX()));//Angulo entre el enemigo y el target, en grados
	angle = angle * 180 / M_PI;
	if (angle < 0)
		angle += 360;
			
	if (eg->currentState == IDLE) {
		if (angle > 297 && angle < 342) {
			if (eg->currentState == IDLE) {
				gameObject->sendMessage("IDLE_TOPRIGHT");
			}
				gameObject->getTransform()->direction.set(1, -1);
		}
		else if (angle > 252 && angle < 297) {
			if (eg->currentState == IDLE) {
				gameObject->sendMessage("IDLE_TOP");
			}
				gameObject->getTransform()->direction.set(0, -1);
		}
		else if (angle > 207 && angle <= 252) {
			if (eg->currentState == IDLE) {
				gameObject->sendMessage("IDLE_TOPLEFT");
			}
				gameObject->getTransform()->direction.set(-1, -1);
		}
		else if (angle > 162 && angle < 207) {
			if (eg->currentState == IDLE) {
				gameObject->sendMessage("IDLE_LEFT");
			}
				gameObject->getTransform()->direction.set(-1, 0);
		}
		else if (angle >= 117 && angle < 162) {
			if (eg->currentState == IDLE) {
				gameObject->sendMessage("IDLE_BOTLEFT");
			}
				gameObject->getTransform()->direction.set(-1, 1);
		}
		else if (angle > 72 && angle < 117) {
			if (eg->currentState == IDLE) {
				gameObject->sendMessage("IDLE_BOT");
			}
				gameObject->getTransform()->direction.set(0, 1);
		}
		else if (angle > 27 && angle < 72) {
			if (eg->currentState == IDLE) {
				gameObject->sendMessage("IDLE_BOTRIGHT");
			}
				gameObject->getTransform()->direction.set(1, 1);
		}
		else {
			if (eg->currentState == IDLE) {
				gameObject->sendMessage("IDLE_RIGHT");
			}
				gameObject->getTransform()->direction.set(1, 0);
		}
	}
	else if (eg->currentState == RUN) {
		if (angle > 225 && angle < 315) {
			gameObject->sendMessage("RUN_TOP");
			gameObject->getTransform()->direction.set(0, -1);
		}
		else if (angle > 135 && angle < 225) {
			gameObject->sendMessage("RUN_LEFT");
			gameObject->getTransform()->direction.set(-1, 0);
		}
		else if (angle > 45 && angle < 135) {
			gameObject->sendMessage("RUN_BOT");
			gameObject->getTransform()->direction.set(0, 1);
		}
		else {
			gameObject->sendMessage("RUN_RIGHT");
			gameObject->getTransform()->direction.set(1, 0);
		}
	}
}
