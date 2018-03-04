#pragma once
#include "ChaseComponent.h"
#include "GameObject.h"


ChaseComponent::ChaseComponent(GameObject* o, GameObject* target, float vel)
{
	gameObject = o;
	type = UpdateC;
	targetObject = target;
	velocity = vel;

}


ChaseComponent::~ChaseComponent()
{
}

void ChaseComponent::update() {
	/*esto requiere un arreglo bastante importante,
	basicamente intento de version chula con angulos y tal
	
	//Obtienes velocidad y posicion del enemigo
	chaserPosition = getGameObject()->getTransform()->position;
	chaserVelocity.set(velocity, velocity);
	chaserVelocity.normalize();
	targetPosition = targetObject->getTransform()->position;
	//angulo entre enemigo y jugador
	//rotas velocidad enemigo
	angle = chaserPosition.angle(targetPosition);
	chaserVelocity.rotate(angle);
	//se normaliza y se multiplica por la magnitud de la velocidad
	chaserVelocity.normalize();
	chaserVelocity*velocity;
	//se asigna la velocidad del enemigo
	getGameObject()->getTransform()->velocity.set(chaserVelocity);
	
	getGameObject()->getTransform()->position.set(chaserPosition + chaserVelocity);

	cout << getGameObject()->getTransform()->position;
	*/

	//version chusta con 8 direcciones
	chaserPosition = getGameObject()->getTransform()->position;
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
	

}