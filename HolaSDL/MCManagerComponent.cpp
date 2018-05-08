#pragma once
#include "MCManagerComponent.h"
#include "MainCharacter.h"
#include "ParticlesManager.h"
#include "HUDManager.h"

MCManagerComponent::MCManagerComponent(MainCharacter* o) : UpdateComponent(static_cast<GameObject*>(o)) {
	mc = o;
	hurtTimer = new Timer();
}

MCManagerComponent::~MCManagerComponent()
{
}

void MCManagerComponent::receiveMessage(Message * msg)
{
	switch (msg->id) {
	case ATTACK1_LEFT:
		break;
	case ATTACK2_LEFT:
		break;
	case ATTACK3_LEFT:
		break;
	case ATTACK1_RIGHT:
		break;
	case ATTACK2_RIGHT:

		break;
	case ATTACK3_RIGHT:
		break;
	case ATTACK1_TOPLEFT:
		break;
	case ATTACK2_TOPLEFT:
		break;
	case ATTACK3_TOPLEFT:
		break;
	case ATTACK1_TOPRIGHT:
		break;
	case ATTACK2_TOPRIGHT:
		break;
	case ATTACK3_TOPRIGHT:
		break;
	case ATTACK1_BOTLEFT:
		break;
	case ATTACK2_BOTLEFT:
		break;
	case ATTACK3_BOTLEFT:
		break;
	case ATTACK1_BOTRIGHT:
		break;
	case ATTACK2_BOTRIGHT:
		break;
	case ATTACK3_BOTRIGHT:
		break;
	case RUN_LEFT:
		break;
	case RUN_RIGHT:
		break;
	case RUN_TOP:
		break;
	case RUN_BOT:
		break;
	case IDLE_LEFT:
		break;
	case IDLE_RIGHT:
		break;
	case IDLE_TOP:
		break;
	case IDLE_BOT:
		break;
	case HOOK_WALL:
		mc->setMCState(MCState::Dash);
		break;
	case HOOK_ENEMY:
		break;
	case HOOK_EXTEND:
		break;
	case HOOK_FAIL:
		break;
	case HOOK_EMPTY:
		break;
	case HOOK_STOP:
		mc->setMCState(MCState::DashEnd);
		mc->setMovable(true);
		break;
	case MC_SHOT:
		//gunTimer->restart();
		mc->setMCState(MCState::Shot);
		break;
	case MC_HOOKSHOT:
		mc->setMCState(MCState::HookShot);
		break;
	case ENEMY_BULLET_COLLISION:
		HurtMC(5.0);
		break;
	case STALKER_ATTACK:
		HurtMC(10.0);
		break;
	case BOSS1_ATTACK:
		HurtMC(static_cast<BossAttack*>(msg)->damage);
		break;
	case WHEEL_HIT:
		HurtMC(static_cast<WheelHit*>(msg)->damage);
		break;
	case MC_DEATH:
		mc->setMCState(MCState::Death);
		break;
	}
}

void MCManagerComponent::update()
{
	if (hurt) {//Solo entra cuando el personaje es invencible
		gameObject->setInvincibility(true);
		hurtTimer->update();//Activa el contador, y cuando pasa el tiempo límite lo vuelve vulnerable
		if (hurtTimer->TimeSinceTimerCreation > hurtTime) {
			gameObject->setInvincibility(false);
			hurtTimer->restart();
			hurt= false;
		}
	}
	else {
		gameObject->setInvincibility(false);
		hurtTimer->restart();
	}
	//Aqui va lo de HandleANimationstates con el hurtTimer etc.
}

//Crea particula de sangre, cambia estado de MC a HURT y le resta vida, si muere envia el mensaje.
void MCManagerComponent::HurtMC(float dmg) {
	ParticlesManager::getInstance()->getParticle(ParticleType::Blood, mc->getCenterPos().getX() - 40, mc->getCenterPos().getY() - 40);
	mc->setMCState(MCState::Hurt);
	mc->addHP(-dmg);
	Message msg2(HURT);
	this->gameObject->sendMessage(&msg2);
	
	hurt = true;
	//mc->substractHP(dmg);
	//HUDManager::getInstance()->changeLife(-dmg);

	if (mc->getActualHP() <= 0) {
		Message msg(MC_DEATH);
		//Envia a todos los componentes del MC el msg de muerte
		this->gameObject->sendMessage(&msg);
	}
}