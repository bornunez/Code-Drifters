#include "TurretAnimationComponent.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"
#include "MainCharacter.h"
#include "Enemy.h"
#include "Random.h"
#include "ParticlesManager.h"

TurretAnimationComponent::TurretAnimationComponent(Enemy* o, GameObject* target,std::map<const char*, Animation*> anim, float extraStun) : RenderComponent(o)
{
	animations = anim;
	this->target = target;
	alertTimer = new Timer();
	et = o;
	specificStun = extraStun;

	gameObject->changeCurrentAnimation("WAITING");
	gameObject->getCurrentAnimation()->startAnimation();
}


TurretAnimationComponent::~TurretAnimationComponent()
{
}

void TurretAnimationComponent::render()
{
	handleAnimations();
	gameObject->getCurrentAnimation()->runAnimation();

}

void TurretAnimationComponent::receiveMessage(Message * msg)
{
	switch (msg->id) {

	case TURRET_IDLE:
		gameObject->changeCurrentAnimation("WAITING");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case TURRET_ALERT:
		gameObject->changeCurrentAnimation("PREPARING");
		gameObject->getCurrentAnimation()->startAnimation();
		alertTimer->restart();
		break;
	case TURRET_ALERT_OVER:
		gameObject->changeCurrentAnimation("DISAMBLING");
		gameObject->getCurrentAnimation()->startAnimation();
		alertTimer->restart();
		break;
	case IDLE_LEFT:
		gameObject->changeCurrentAnimation("LEFT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case IDLE_RIGHT:
		gameObject->changeCurrentAnimation("RIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case IDLE_TOP:
		gameObject->changeCurrentAnimation("TOP");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case IDLE_BOT:
		gameObject->changeCurrentAnimation("BOT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case IDLE_TOPLEFT:
		gameObject->changeCurrentAnimation("TOPLEFT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case IDLE_BOTLEFT:
		gameObject->changeCurrentAnimation("BOTLEFT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case IDLE_TOPRIGHT:
		gameObject->changeCurrentAnimation("TOPRIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case IDLE_BOTRIGHT:
		gameObject->changeCurrentAnimation("BOTRIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case MC_BULLET_COLLISION: {
		if (!et->isDead()) {
			if (!et->isStunned())
				ParticlesManager::getInstance()->getParticle(ParticleType::Stun, gameObject->getTransform()->position.getX()-25, 
					gameObject->getTransform()->position.getY()-10, static_cast<MCBulletStun*>(msg)->stunTime + specificStun);
			}
		}
	}
}
	

void TurretAnimationComponent::handleAnimations()
{
	if (!gameObject->isDead()) {
		if (!et->isStunned()) {
			if (et->enemyState == EnemyState::Run) {
				alertTimer->update();
				if (alertTimer->TimeSinceTimerCreation > .6) {
					et->enemyState = EnemyState::Attack;
				}
			}

			else if (et->enemyState == EnemyState::Charge) {
				alertTimer->update();
				if (alertTimer->TimeSinceTimerCreation > .6) {
					et->enemyState = EnemyState::Idle;
					Message msg(TURRET_IDLE);
					gameObject->sendMessage(&msg);
				}
			}

			else if (et->enemyState == EnemyState::Attack) {
				Message msg(IDLE_TOPRIGHT);
				gameObject->sendMessage(&msg);

				//C�LCULO DEL �NGULO ENTRE EL TARGET Y EL ENEMIGO
				Vector2D displayCenterPos = gameObject->getDisplayCenterPos();
				float angle = (atan2(target->getDisplayCenterPos().getY() - displayCenterPos.getY(), target->getDisplayCenterPos().getX() - displayCenterPos.getX()));
				//Angulo entre el enemigo y el target, en grados
				angle = angle * 180 / M_PI;
				if (angle < 0)
					angle += 360;
				if (angle > 297 && angle < 342) {
					Message msg(IDLE_TOPRIGHT);
					gameObject->sendMessage(&msg);
					gameObject->getTransform()->direction.set(1, -1);
				}
				else if (angle > 252 && angle < 297) {
					Message msg(IDLE_TOP);
					gameObject->sendMessage(&msg);
					gameObject->getTransform()->direction.set(0, -1);
				}
				else if (angle > 207 && angle <= 252) {
					Message msg(IDLE_TOPLEFT);
					gameObject->sendMessage(&msg);
					gameObject->getTransform()->direction.set(-1, -1);
				}
				else if (angle > 162 && angle < 207) {
					Message msg(IDLE_LEFT);
					gameObject->sendMessage(&msg);
					gameObject->getTransform()->direction.set(-1, 0);
				}
				else if (angle >= 117 && angle < 162) {
					Message msg(IDLE_BOTLEFT);
					gameObject->sendMessage(&msg);
					gameObject->getTransform()->direction.set(-1, 1);
				}
				else if (angle > 72 && angle < 117) {
					Message msg(IDLE_BOT);
					gameObject->sendMessage(&msg);
					gameObject->getTransform()->direction.set(0, 1);
				}
				else if (angle > 27 && angle < 72) {
					Message msg(IDLE_BOTRIGHT);
					gameObject->sendMessage(&msg);
					gameObject->getTransform()->direction.set(1, 1);
				}
				else {
					Message msg(IDLE_RIGHT);
					gameObject->sendMessage(&msg);
					gameObject->getTransform()->direction.set(1, 0);
				}
			}
		}

	}
}



