#include "StalkerAnimationComponent.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"
#include "EnemyStalker.h"

StalkerAnimationComponent::StalkerAnimationComponent(EnemyStalker* o, GameObject* target,std::map<const char*, Animation*> anim, float hTime, float delayTime) : RenderComponent(o)
{
	animations = anim;
	gameObject->changeCurrentAnimation("RUN");
	this->target = target;
	this->es = o;
	attackDelay = delayTime;
	hurtTime = hTime;
}


StalkerAnimationComponent::~StalkerAnimationComponent()
{
}

void StalkerAnimationComponent::render()
{
	handleAnimation();
	gameObject->getCurrentAnimation()->runAnimation();
}

void StalkerAnimationComponent::receiveMessage(Message* msg)
{
	switch (msg->id) {
		case ENEMY_SPAWN:
			hurtTimer.restart();
			chargeTimer.restart();
			break;
		case STALKER_RUN:
			gameObject->changeCurrentAnimation("RUN");
			gameObject->getCurrentAnimation()->startAnimation();
			break;
		case STALKER_CHARGE:
			gameObject->changeCurrentAnimation("CHARGE");
			gameObject->getCurrentAnimation()->startAnimation();
			chargeTimer.restart();
			break;
		case STALKER_ATTACK:
			gameObject->changeCurrentAnimation("ATTACK");
			gameObject->getCurrentAnimation()->startAnimation();
			break;
		case HURT:
			gameObject->changeCurrentAnimation("HURT");
			gameObject->getCurrentAnimation()->startAnimation();
			hurtTimer.restart();
			es->enemyState = EnemyState::Hurt;
			break;
		case GUN_STUN:
			gameObject->changeCurrentAnimation("STUN");
			gameObject->getCurrentAnimation()->startAnimation();
			break;
		case STUN_OFF:
			gameObject->changeCurrentAnimation("RUN");
			gameObject->getCurrentAnimation()->startAnimation();
			break;
		case ENEMY_DEATH:
			gameObject->changeCurrentAnimation("DEATH");
			gameObject->getCurrentAnimation()->startAnimation();
			break;
	}
}

void StalkerAnimationComponent::handleAnimation()
{
	if (!gameObject->isDead()) {
		if (!es->isStunned()) {
			if (es->enemyState == EnemyState::Hurt) {
				hurtTimer.update();
				if (hurtTimer.TimeSinceTimerCreation > hurtTime) {
					es->enemyState = EnemyState::Run;
					gameObject->changeCurrentAnimation("RUN");
				}
			}

			else if (es->enemyState == EnemyState::Charge) {
				chargeTimer.update();
				if (chargeTimer.TimeSinceTimerCreation > attackDelay) {
					es->enemyState = EnemyState::Attack;
					Message msg(STALKER_ATTACK);
					es->sendMessage(&msg);

				}
			}

			if (gameObject->getCenterPos().getX() > target->getCenterPos().getX() && es->facing == RIGHT) {//Si está mirando a la izq gira a la derecha 

				gameObject->flipAllAnimations(SDL_FLIP_HORIZONTAL);
				es->facing = LEFT;

			}
			else if (gameObject->getCenterPos().getX() <= target->getCenterPos().getX() && es->facing == LEFT) {
				gameObject->flipAllAnimations(SDL_FLIP_NONE);
				es->facing = RIGHT;
			}
		}
	}
}