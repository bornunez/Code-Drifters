#include "GunnerAnimationComponent.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"
#include "MainCharacter.h"
#include "EnemyGunner.h"
#include "Random.h"
GunnerAnimationComponent::GunnerAnimationComponent(Enemy* o, GameObject* target,std::map<const char*, Animation*> anim) : RenderComponent(o)
{
	eg = o;
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

void GunnerAnimationComponent::receiveMessage(Message * msg)
{
	switch (msg->id) {
	case ENEMY_SPAWN:
		hurtTimer.restart();
		break;
	case RUN_LEFT:
		gameObject->changeCurrentAnimation("RUN_LEFT");
		break;
	case RUN_RIGHT:
		gameObject->changeCurrentAnimation("RUN_RIGHT");
		break;
	case RUN_TOP:
		gameObject->changeCurrentAnimation("RUN_TOP");
		break;
	case RUN_BOT:
		gameObject->changeCurrentAnimation("RUN_BOT");
		break;
	case IDLE_LEFT:
		gameObject->changeCurrentAnimation("IDLE_LEFT");
		break;
	case IDLE_RIGHT:
		gameObject->changeCurrentAnimation("IDLE_RIGHT");
		break;
	case IDLE_TOP:
		gameObject->changeCurrentAnimation("IDLE_TOP");
		break;
	case IDLE_BOT:
		gameObject->changeCurrentAnimation("IDLE_BOT");
		break;
	case IDLE_TOPLEFT:
		gameObject->changeCurrentAnimation("IDLE_TOPLEFT");
		break;
	case IDLE_BOTLEFT:
		gameObject->changeCurrentAnimation("IDLE_BOTLEFT");
		break;
	case IDLE_TOPRIGHT:
		gameObject->changeCurrentAnimation("IDLE_TOPRIGHT");
		break;
	case IDLE_BOTRIGHT:
		gameObject->changeCurrentAnimation("IDLE_BOTRIGHT");
		break;
	case SHOT_LEFT:
		gameObject->changeCurrentAnimation("SHOT_LEFT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case SHOT_RIGHT:
		gameObject->changeCurrentAnimation("SHOT_RIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case SHOT_TOP:
		gameObject->changeCurrentAnimation("SHOT_TOP");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case SHOT_BOT:
		gameObject->changeCurrentAnimation("SHOT_BOT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case SHOT_TOPLEFT:
		gameObject->changeCurrentAnimation("SHOT_TOPLEFT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case SHOT_BOTLEFT:
		gameObject->changeCurrentAnimation("SHOT_BOTLEFT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case SHOT_TOPRIGHT:
		gameObject->changeCurrentAnimation("SHOT_TOPRIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case SHOT_BOTRIGHT:
		gameObject->changeCurrentAnimation("SHOT_BOTRIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case HURT:
		hurtAnimations();
		break;
	case GUN_STUN:
		stunAnimations();
		break;
	case ENEMY_DEATH:
		deathAnimations();
		break;
	}
	
}

void GunnerAnimationComponent::handleAnimations()
{
	if (!gameObject->isDead()) {
		if (!eg->isStunned()) {
			if (eg->enemyState == EnemyState::Hurt) {//Timer relacionado con la animación de recibir daño
				hurtTimer.update();
				if (hurtTimer.TimeSinceTimerCreation > 0.2) {
					eg->enemyState = EnemyState::Idle;
				}
			}


			Transform* gunnerT = gameObject->getTransform();
			if (eg->enemyState != EnemyState::Shoot && eg->enemyState != EnemyState::Hurt) {
				if (gunnerT->velocity.getX() != 0 && gunnerT->velocity.getY() != 0) {
					eg->enemyState = EnemyState::Run;
				}
				else {
					eg->enemyState = EnemyState::Idle;
				}
			}


			//CÁLCULO DEL ÁNGULO ENTRE EL TARGET Y EL ENEMIGO
			Vector2D displayCenterPos = gameObject->getDisplayCenterPos();
			float angle = (atan2(target->getDisplayCenterPos().getY() - displayCenterPos.getY(), target->getDisplayCenterPos().getX() - displayCenterPos.getX()));//Angulo entre el enemigo y el target, en grados
			angle = angle * 180 / M_PI;
			if (angle < 0)
				angle += 360;

			if (eg->enemyState == EnemyState::Idle) {
				if (angle > 297 && angle < 342) {
					if (eg->enemyState == EnemyState::Idle) {
						Message msg(IDLE_TOPRIGHT);
						gameObject->sendMessage(&msg);
					}
					gameObject->getTransform()->direction.set(1, -1);
				}
				else if (angle > 252 && angle < 297) {
					if (eg->enemyState == EnemyState::Idle) {
						Message msg(IDLE_TOP);
						gameObject->sendMessage(&msg);
					}
					gameObject->getTransform()->direction.set(0, -1);
				}
				else if (angle > 207 && angle <= 252) {
					if (eg->enemyState == EnemyState::Idle) {
						Message msg(IDLE_TOPLEFT);
						gameObject->sendMessage(&msg);
					}
					gameObject->getTransform()->direction.set(-1, -1);
				}
				else if (angle > 162 && angle < 207) {
					if (eg->enemyState == EnemyState::Idle) {
						Message msg(IDLE_LEFT);
						gameObject->sendMessage(&msg);
					}
					gameObject->getTransform()->direction.set(-1, 0);
				}
				else if (angle >= 117 && angle < 162) {
					if (eg->enemyState == EnemyState::Idle) {
						Message msg(IDLE_BOTLEFT);
						gameObject->sendMessage(&msg);
					}
					gameObject->getTransform()->direction.set(-1, 1);
				}
				else if (angle > 72 && angle < 117) {
					if (eg->enemyState == EnemyState::Idle) {
						Message msg(IDLE_BOT);
						gameObject->sendMessage(&msg);
					}
					gameObject->getTransform()->direction.set(0, 1);
				}
				else if (angle > 27 && angle < 72) {
					if (eg->enemyState == EnemyState::Idle) {
						Message msg(IDLE_BOTRIGHT);
						gameObject->sendMessage(&msg);
					}
					gameObject->getTransform()->direction.set(1, 1);
				}
				else {
					if (eg->enemyState == EnemyState::Idle) {
						Message msg(IDLE_RIGHT);
						gameObject->sendMessage(&msg);
					}
					gameObject->getTransform()->direction.set(1, 0);
				}
			}
			else if (eg->enemyState == EnemyState::Run) {
				if (angle > 225 && angle < 315) {
					Message msg(RUN_TOP);
					gameObject->sendMessage(&msg);
					gameObject->getTransform()->direction.set(0, -1);
				}
				else if (angle > 135 && angle < 225) {
					Message msg(RUN_LEFT);
					gameObject->sendMessage(&msg);
					gameObject->getTransform()->direction.set(-1, 0);
				}
				else if (angle > 45 && angle < 135) {
					Message msg(RUN_BOT);
					gameObject->sendMessage(&msg);
					gameObject->getTransform()->direction.set(0, 1);
				}
				else {
					Message msg(RUN_RIGHT);
					gameObject->sendMessage(&msg);
					gameObject->getTransform()->direction.set(1, 0);
				}
			}
		}
	}
}

void GunnerAnimationComponent::hurtAnimations()
{
	int rnd = Random::randomInt(0, 1);
	hurtTimer.restart();
	eg->enemyState = EnemyState::Hurt;
	if (gameObject->getTransform()->direction.getX() == 1) {
		if (rnd == 1) {
			gameObject->changeCurrentAnimation("DAMAGE_RIGHT1");
		}
		else gameObject->changeCurrentAnimation("DAMAGE_RIGHT2");
	}
	else {
		if (rnd == 1) {
			gameObject->changeCurrentAnimation("DAMAGE_LEFT1");
		}
		else  gameObject->changeCurrentAnimation("DAMAGE_LEFT2");
	}
	gameObject->getCurrentAnimation()->startAnimation();
}

void GunnerAnimationComponent::stunAnimations()
{
	int rnd = Random::randomInt(0, 1);
	if (gameObject->getTransform()->direction.getX() == 1) {
		if (rnd == 1) {
			gameObject->changeCurrentAnimation("STUN_RIGHT1");
		}
		else gameObject->changeCurrentAnimation("STUN_RIGHT2");
	}
	else {
		if (rnd == 1) {
			gameObject->changeCurrentAnimation("STUN_LEFT1");
		}
		else  gameObject->changeCurrentAnimation("STUN_LEFT2");
	}
	gameObject->getCurrentAnimation()->startAnimation();
}

void GunnerAnimationComponent::deathAnimations()
{
	if (gameObject->getTransform()->direction.getX() == 1) {
		gameObject->changeCurrentAnimation("DEATH_RIGHT");
	}
	else {
		gameObject->changeCurrentAnimation("DEATH_LEFT");
	}
	gameObject->getCurrentAnimation()->startAnimation();
}
