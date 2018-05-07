#pragma once
#include "BomberComponent.h"
#include "GameObject.h"
#include <cmath>
#include "MainCharacter.h"
#include "Enemy.h"

BomberComponent::BomberComponent(Enemy* e, GameObject* target, float dist) : UpdateComponent(e)
{
	targetObject = target;
	distancia = dist;
	eb = e;
	eb->enemyState = EnemyState::Run;
}


BomberComponent::~BomberComponent()
{
}


void BomberComponent::update() {

	if (!gameObject->isDead()) {
		Transform* bomberT = gameObject->getTransform();
		Transform* targetT = targetObject->getTransform();
		if (angle > 365) angle = 0;

		if (!eb->isStunned()) {
			Vector2D auxVel;
			Vector2D auxPos;
			if ((abs(targetT->position.getX() - bomberT->position.getX() - 25) + abs(targetT->position.getY() - bomberT->position.getY() - 25)) <= distancia + 50) {
				if (!rotating) {
					rotating = true;
					angle = targetT->position.angle(bomberT->position);
				}
				if (eb->enemyState == EnemyState::Run) {
					//Circular Movement
					//Auxpos marca punto en trayectoria circular alrededor del target, bomber asume esa position como target y lo persigue
					angle += angleVel;
					auxPos.set(targetT->position.getX() - 25 + cos(angle)*(distancia - 50), targetT->position.getY() - 25 + sin(angle)*(distancia - 50));
					auxVel.set(auxPos - bomberT->position);
					auxVel.normalize();
					bomberT->velocity.set(auxVel);
					eb->setMovable(true);
				}
			}

			//Regular chase
			else if(eb->enemyState == EnemyState::Run) {
				if (rotating) {
					rotating = false;
				}	
				//vectorentre enemigo y objetivo
				auxVel.set(targetT->position - bomberT->position);

				//se normaliza y se multiplica por la magnitud de la velocidad
				auxVel.normalize();

				//se asigna la velocidad del enemigo y se actualiza la posicion
				bomberT->velocity.set(auxVel);
				eb->setMovable(true);

			}
		}
	}

}



	

