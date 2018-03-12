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
	

	
	//Obtienes velocidad y posicion del enemigo
	chaserPosition = getGameObject()->getTransform()->position;

	targetPosition = targetObject->getTransform()->position;
	//vectro entre enemigo y jugador
	chaserVelocity.set(targetPosition - chaserPosition);
	//se normaliza y se multiplica por la magnitud de la velocidad
	chaserVelocity.normalize();

	chaserVelocity = chaserVelocity * velocity;

	//se asigna la velocidad del enemigo
	getGameObject()->getTransform()->velocity.set(chaserVelocity);
	
	getGameObject()->getTransform()->position.set(getGameObject()->getTransform()->position + getGameObject()->getTransform()->velocity);

	
	

	//version chusta con 8 direcciones
	/*chaserPosition = getGameObject()->getTransform()->position;
	targetPosition = targetObject->getTransform()->position;
	if (chaserPosition.getX() > targetPosition.getX()) {
		chaserVelocity.setX(-velocity);
	}
	else chaserVelocity.setX(velocity);

	if (chaserPosition.getY() > targetPosition.getY()) {
		chaserVelocity.setY(-velocity);
	}
	else chaserVelocity.setY(velocity);

	getGameObject()->getTransform()->position.set(chaserPosition + chaserVelocity);
	
	*/
}