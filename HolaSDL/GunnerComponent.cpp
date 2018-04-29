#pragma once
#include "GunnerComponent.h"
#include "GameObject.h"
#include <cmath>
#include "Bullet.h"
#include "MCBulletComponent.h"
#include "MCBulletRenderComponent.h"
#include "MainCharacter.h"
#include"EnemyGunner.h"
#include "Hook.h"

GunnerComponent::GunnerComponent(GameObject* o, GameObject* target, float dist) : UpdateComponent(o)
{
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

		EnemyGunner* eg = static_cast<EnemyGunner*>(gameObject);

		if (!eg->isStunned()) {
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
	/* horizontal chase
	else {
	if (abs(targetT->position.getX() - gunnerT->position.getX()) > abs(targetT->position.getY() - gunnerT->position.getY())) {
	if (gunnerT->position.getX() > targetT->position.getX()) {
	gunnerT->velocity.setX(-velocity);
	}
	else gunnerT->velocity.setX(velocity);
	}
	else {
	if (gunnerT->position.getY() > targetT->position.getY()) {
	gunnerT->velocity.setY(-velocity);
	}
	else gunnerT->velocity.setY(velocity);
	}
	}
	*/
}

void GunnerComponent::receiveMessage(Message * msg)
{
	switch (msg->id) {
	case HIT_WALL:
		EnemyGunner * eg = static_cast<EnemyGunner*>(gameObject);
		if (eg->getEnemyState() == EnemyState::Hooked) {//Si está siendo enganchado y choca con la pared, se desengancha
			static_cast<MainCharacter*>(targetObject)->getHook().setHookStatus(HookStatus::STOP);
			Message msg(HOOK_STOP);
			static_cast<MainCharacter*>(targetObject)->sendMessage(&msg);
			eg->getEnemyState() == EnemyState::Idle;
			static_cast<MainCharacter*>(targetObject)->setMCState(MCState::Idle);

		}
		break;
	}
}



	

