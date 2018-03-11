#pragma once
#include "GunnerComponent.h"
#include "GameObject.h"
#include <cmath>



GunnerComponent::GunnerComponent(GameObject* o, GameObject* target, float vel, float dist) : UpdateComponent(o)
{
	targetObject = target;
	velocity = vel;
	distancia = dist;

}


GunnerComponent::~GunnerComponent()
{
}


void GunnerComponent::update() {

	Transform* gunnerT = gameObject->getTransform();
	Transform* targetT = targetObject->getTransform();

	if ((abs(targetT->position.getX() - gunnerT->position.getX()) + abs(targetT->position.getY() - gunnerT->position.getY())) <= distancia) {
		getGameObject()->getTransform()->velocity.set(0.0, 0.0);
}


	//Regular chase
	else {
		Vector2D auxVel;

		//vectorentre enemigo y objetivo
		auxVel.set(targetT->position - gunnerT->position);

		//se normaliza y se multiplica por la magnitud de la velocidad
		auxVel.normalize();
		auxVel = auxVel * velocity;

		//se asigna la velocidad del enemigo y se actualiza la posicion
		gunnerT->velocity.set(auxVel);
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
	gunnerT->position.set(gunnerT->position + gunnerT->velocity);
}
