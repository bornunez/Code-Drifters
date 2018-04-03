#pragma once
#include "ChaseComponent.h"
#include "GameObject.h"


ChaseComponent::ChaseComponent(GameObject* o, GameObject* target) : UpdateComponent(o)
{
	targetObject = target;
	

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

	//se normaliza 
	auxVel.normalize();
	

	//se asigna la velocidad del enemigo 
	chaserT->velocity.set(auxVel);
}

