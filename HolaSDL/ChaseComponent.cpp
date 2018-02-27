#include "ChaseComponent.h"



ChaseComponent::ChaseComponent()
{
}


ChaseComponent::~ChaseComponent()
{
}

void ChaseComponent::update() {
	//Obtienes velocidad y posicion del enemigo
	position = gameObject->getTransform()->position;
	velocity = gameObject->getTransform()->velocity;
	//target = gameObject-> getCharacter?, enemigo debería tener un puntero a maincharacter
	//angulo entre enemigo y jugador
	//rotas velocidad enemigo
	angle = position.angle(target);
	velocity.rotate(angle);
	//se normaliza y se multiplica por la magnitud de la velocidad
	velocity.normalize();
	//velocity*velocidad;
	//se asigna la velocidad del enemigo
	gameObject->getTransform()->velocity.set(velocity);
	

}