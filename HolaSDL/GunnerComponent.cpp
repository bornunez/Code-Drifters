#pragma once
#include "GunnerComponent.h"
#include "GameObject.h"
#include <cmath>
#include "Bullet.h"
#include "MCBulletComponent.h"
#include "MCBulletRenderComponent.h"
#include "MainCharacter.h"
#include "EnemyGunner.h"
#include "Hook.h"

GunnerComponent::GunnerComponent(Enemy* o, MainCharacter* target, float dist) : UpdateComponent(o)
{
	eg = o;
	targetObject = target;
	distancia = dist;

}


GunnerComponent::~GunnerComponent()
{
}


void GunnerComponent::update() {

	if (!gameObject->isDead()) {
		Transform* gunnerT = gameObject->getTransform();
		Transform* targetT = targetObject->getTransform();
		if ((abs(targetT->position.getX() - gunnerT->position.getX()) + abs(targetT->position.getY() - gunnerT->position.getY())) <= 800 && !eg->isStunned()) {
			if ((abs(targetT->position.getX() - gunnerT->position.getX()) + abs(targetT->position.getY() - gunnerT->position.getY())) <= distancia) {
				gameObject->getTransform()->velocity.set(0.0, 0.0);
				eg->setMovable(false);
			}

			//Regular chase
			else {
				Vector2D auxVel;

				//vectorentre enemigo y objetivo
				auxVel.set(targetT->position - gunnerT->position);

				//se normaliza y se multiplica por la magnitud de la velocidad
				auxVel.normalize();

				//se asigna la velocidad del enemigo y se actualiza la posicion
				gunnerT->velocity.set(auxVel);
				eg->setMovable(true);

			}
		}
		else {
			gameObject->getTransform()->velocity.set({ 0,0 });
			eg->setMovable(false);
		}

	}
}

void GunnerComponent::receiveMessage(Message * msg)
{
	switch (msg->id) {
	case HIT_WALL:
		if (eg->getEnemyState() == EnemyState::Hooked) {//Si está siendo enganchado y choca con la pared, se desengancha
			targetObject->getHook()->setHookStatus(HookStatus::STOP);
			Message msg(HOOK_STOP);
			targetObject->sendMessage(&msg);
			eg->getEnemyState() == EnemyState::Idle;
			targetObject->setMCState(MCState::Idle);

		}
		break;
	}
}



	

