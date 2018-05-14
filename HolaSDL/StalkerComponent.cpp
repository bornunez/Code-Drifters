#pragma once
#include "StalkerComponent.h"
#include "MainCharacter.h"
#include "Enemy.h"
#include "Hook.h"

StalkerComponent::StalkerComponent(Enemy * e, MainCharacter * target, float cDelay, float aDelay, float aTime, float velMultiplier) : ChaseComponent(e, target, 200),
ChargeComponent(e, target, aDelay, aTime, velMultiplier), UpdateComponent(e)
{
	timer = new Timer();
	chargeDelay = cDelay;
	attackDelay = aDelay;
	attackTime = aTime;
	es = e;
	es->enemyState = EnemyState::Run;
	this->target = target;
}

StalkerComponent::~StalkerComponent()
{
}
void StalkerComponent::receiveMessage(Message * msg)
{
	switch (msg->id) {
	case HIT_WALL:;
		if (es->getEnemyState() == EnemyState::Hooked) {//Si está siendo enganchado y choca con la pared, se desengancha
			target->getHook().setHookStatus(HookStatus::STOP);
			Message msg(HOOK_STOP);
			target->sendMessage(&msg);
			es->getEnemyState() == EnemyState::Idle;
			target->setMCState(MCState::Idle);

		}
		break;

	case ENEMY_SPAWN:
		timer->restart();
		break;
	}
}

void StalkerComponent::update()
{
	if (!gameObject->isDead()) {
		timer->update();

		;

		if (!es->isStunned()) {
			if ((es->enemyState != EnemyState::Charge && es->enemyState != EnemyState::Attack) && timer->TimeSinceTimerCreation >= chargeDelay) {
				es->enemyState = EnemyState::Charge;
				ChargeComponent::startCharge();
				timer->restart();
				Message msg(STALKER_CHARGE);
				es->sendMessage(&msg);
			}
			else if ((es->enemyState == EnemyState::Charge || es->enemyState == EnemyState::Attack) && timer->TimeSinceTimerCreation >= attackDelay + attackTime + .1) {
				es->enemyState = EnemyState::Run;
				es->getTransform()->speed = es->baseSpeed;
				timer->restart();
				Message msg(STALKER_RUN);
				es->sendMessage(&msg);

			}
			if (es->enemyState == EnemyState::Charge || es->enemyState == EnemyState::Attack)
				ChargeComponent::update();

			else if (es->enemyState == EnemyState::Run)
				ChaseComponent::update();
		}
		else {
			gameObject->getTransform()->velocity.set({ 0,0 });
		}
	}
}
