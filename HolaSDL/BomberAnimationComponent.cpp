#include "BomberAnimationComponent.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"
#include "EnemyBomber.h"

BomberAnimationComponent::BomberAnimationComponent(EnemyBomber* o, GameObject* target, std::map<const char*, Animation*> anim, float hTime) : RenderComponent(o)
{
	animations = anim;
	this->target = target;
	this->eb = o;
	hurtTimer = new Timer();
	hurtTime = hTime;
	gameObject->changeCurrentAnimation("RUNLEFT");
	gameObject->getCurrentAnimation()->startAnimation();
}


BomberAnimationComponent::~BomberAnimationComponent()
{
}

void BomberAnimationComponent::render()
{
	handleAnimation();
	gameObject->getCurrentAnimation()->runAnimation();
}

void BomberAnimationComponent::receiveMessage(Message* msg)
{
	switch (msg->id) {
	case RUN_LEFT:
		gameObject->changeCurrentAnimation("RUNLEFT");
		break;
	case RUN_RIGHT:
		gameObject->changeCurrentAnimation("RUNRIGHT");
		break;


	case SHOT_LEFT:
		gameObject->changeCurrentAnimation("ATTACKLEFT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case SHOT_RIGHT:
		gameObject->changeCurrentAnimation("ATTACKRIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;

	case HURT:
		hurtAnimations();
		break;

	case ENEMY_DEATH:
		deathAnimations();
		break;

	}
}

void BomberAnimationComponent::handleAnimation()
{
	if (!gameObject->isDead() && !eb->isStunned()) {

		//CÁLCULO DEL ÁNGULO ENTRE EL TARGET Y EL ENEMIGO
		Vector2D displayCenterPos = gameObject->getDisplayCenterPos();
		float angle = (atan2(target->getDisplayCenterPos().getY() - displayCenterPos.getY(), target->getDisplayCenterPos().getX() - displayCenterPos.getX()));//Angulo entre el enemigo y el target, en grados
		angle = angle * 180 / M_PI;
		if (angle < 0)
			angle += 360;

		if (eb->enemyState == EnemyState::Hurt) {
			hurtTimer->update();
			if (hurtTimer->TimeSinceTimerCreation > hurtTime) {
				eb->enemyState = EnemyState::Run;
			}
		}

		if (eb->enemyState == EnemyState::Run) {
				//Animacion run según ángulo
				if (angle > 90 && angle < 270) {
					Message msg(RUN_LEFT);
					gameObject->sendMessage(&msg);
				}
				else {
					Message msg(RUN_RIGHT);
					gameObject->sendMessage(&msg);
				}
			}
	}

}

void BomberAnimationComponent::hurtAnimations()
{
	Vector2D displayCenterPos = gameObject->getDisplayCenterPos();
	float angle = (atan2(target->getDisplayCenterPos().getY() - displayCenterPos.getY(), target->getDisplayCenterPos().getX() - displayCenterPos.getX()));//Angulo entre el enemigo y el target, en grados
	angle = angle * 180 / M_PI;
	if (angle < 0)
		angle += 360;

	hurtTimer->restart();
	eb->enemyState = EnemyState::Hurt;

	if (angle > 90 && angle < 270)	gameObject->changeCurrentAnimation("HURTLEFT");

	else gameObject->changeCurrentAnimation("HURTRIGHT");

	gameObject->getCurrentAnimation()->startAnimation();
}

void BomberAnimationComponent::deathAnimations()
{
	Vector2D displayCenterPos = gameObject->getDisplayCenterPos();
	float angle = (atan2(target->getDisplayCenterPos().getY() - displayCenterPos.getY(), target->getDisplayCenterPos().getX() - displayCenterPos.getX()));//Angulo entre el enemigo y el target, en grados
	angle = angle * 180 / M_PI;
	if (angle < 0)
		angle += 360;

	if (angle > 90 && angle < 270)	gameObject->changeCurrentAnimation("DEATHLEFT");

	else gameObject->changeCurrentAnimation("DEATHRIGHT");

	gameObject->getCurrentAnimation()->startAnimation();
}

