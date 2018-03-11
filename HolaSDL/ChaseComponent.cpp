#pragma once
#include "ChaseComponent.h"
#include "GameObject.h"


ChaseComponent::ChaseComponent(GameObject* o, GameObject* target, float vel) : UpdateComponent(o)
{
	targetObject = target;
	velocity = vel;

}


ChaseComponent::~ChaseComponent()
{
}

void ChaseComponent::update() {
	
	//Obtienes transfroms de enemigo y objetivo (por limpieza)
	Transform* chaserT = gameObject->getTransform();
	Transform* targetT = targetObject->getTransform();

	Vector2D auxVel;

	//vectorentre enemigo y objetivo
	auxVel.set(targetT->position - chaserT->position);

	//se normaliza y se multiplica por la magnitud de la velocidad
	auxVel.normalize();
	auxVel = auxVel * velocity;

	//se asigna la velocidad del enemigo y se actualiza la posicion
	chaserT->velocity.set(auxVel);
	chaserT->position.set(chaserT->position + chaserT->velocity);

	

}