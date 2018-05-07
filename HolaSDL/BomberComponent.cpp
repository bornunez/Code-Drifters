#pragma once
#include "BomberComponent.h"
#include "GameObject.h"
#include <cmath>
#include "MainCharacter.h"
#include "Enemy.h"

BomberComponent::BomberComponent(GameObject* o, GameObject* target, float dist) : UpdateComponent(o)
{
	targetObject = target;
	distancia = dist;
	eg = static_cast<Enemy*>(gameObject);
}


BomberComponent::~BomberComponent()
{
}


void BomberComponent::update() {

	if (!gameObject->isDead()) {
		Transform* gunnerT = gameObject->getTransform();
		Transform* targetT = targetObject->getTransform();
		if (angle > 365) angle = 0;

		if (!eg->isStunned()) {
			Vector2D auxVel;
			Vector2D auxPos;
			if ((abs(targetT->position.getX() - gunnerT->position.getX() - 25) + abs(targetT->position.getY() - gunnerT->position.getY() - 25)) <= distancia + 50) {
				if (!rotating) {
					rotating = true;
					angle = targetT->position.angle(gunnerT->position);
				}
				if (eg->enemyState == EnemyState::Run) {
					//Circular Movement
					//Auxpos marca punto en trayectoria circular alrededor del target, bomber asume esa position como target y lo persigue
					angle += angleVel;
					auxPos.set(targetT->position.getX() - 25 + cos(angle)*(distancia - 50), targetT->position.getY() - 25 + sin(angle)*(distancia - 50));
					auxVel.set(auxPos - gunnerT->position);
					auxVel.normalize();
					gunnerT->velocity.set(auxVel);
					eg->setMovable(true);
				}
			}

			//Regular chase
			else {
				if (rotating) {
					rotating = false;
				}	
				//vectorentre enemigo y objetivo
				auxVel.set(targetT->position - gunnerT->position);

				//se normaliza y se multiplica por la magnitud de la velocidad
				auxVel.normalize();

				//se asigna la velocidad del enemigo y se actualiza la posicion
				gunnerT->velocity.set(auxVel);
				eg->setMovable(true);

			}
		}
	}

}



	

