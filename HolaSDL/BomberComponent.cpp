#pragma once
#include "BomberComponent.h"
#include "GameObject.h"
#include <cmath>
#include "Bullet.h"
#include "MCBulletComponent.h"
#include "MCBulletRenderComponent.h"
#include "MainCharacter.h"
#include"Enemy.h"

BomberComponent::BomberComponent(GameObject* o, GameObject* target, float dist) : UpdateComponent(o)
{
	targetObject = target;
	distancia = dist;

}


BomberComponent::~BomberComponent()
{
}


void BomberComponent::update() {

	if (!gameObject->isDead()) {
		Transform* gunnerT = gameObject->getTransform();
		Transform* targetT = targetObject->getTransform();
		//angle = gunnerT->position.angle(targetT->position);
		angle+=.05;
		if (angle > 365) angle = 0;

		Enemy* eg = static_cast<Enemy*>(gameObject);

		if (!eg->isStunned()) {
			Vector2D auxVel;
			if ((abs(targetT->position.getX() - gunnerT->position.getX()) + abs(targetT->position.getY() - gunnerT->position.getY())) <= distancia) {
				//Circular Movement
				//Auxpos marca punto en trayectoria circular alrededor del target, bomber asume esa position como target y lo persigue
				Vector2D auxPos;
				auxPos.set(targetT->position.getX() + cos(angle)*(distancia - 10), targetT->position.getY() + sin(angle)*(distancia - 10));
				auxVel.set(targetT->position - auxPos);
				auxVel.normalize();
				gunnerT->velocity.set(auxVel);
				eg->setMovable(true);
			}

			//Regular chase
			else {
				
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



	

