#pragma once
#include "MCMovementComponent.h"
#include "GameObject.h"
#include "MainCharacter.h"
#include <iostream>



MCMovementComponent::MCMovementComponent(GameObject* o, SDL_Scancode up, SDL_Scancode right, SDL_Scancode down, SDL_Scancode left) :
	upKey(up), rightKey(right),downKey(down),leftKey(left)
{
	gameObject = o;
	type = UpdateC;
	acceleration = 0.05;//Aceleración de la velocidad
	reductionFactor = 0.5;//Aceleración de frenado
	maxVelocity = dynamic_cast<MainCharacter*>(gameObject)->getMaxVelocity();//La velocidad máxima es la del personaje
	velocity.set(0, 0);
	direction.set(0, 1);//Empieza mirando hacia abajo
}


MCMovementComponent::~MCMovementComponent()
{
}
void MCMovementComponent::update()
{	
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	SDL_PumpEvents();
	//continuous-response keys
	if (keystate[leftKey])
	{
		direction.setX(-1);		
		velocity.setX(velocity.getX() + acceleration);		
	}
	else if (keystate[rightKey])
	{
		direction.setX(1);
		velocity.setX(velocity.getX() + acceleration);		
	}
	else {//Si no se mueve en horizontal entonces frena
		velocity.setX(velocity.getX()*reductionFactor);
	}
	if (keystate[upKey])
	{
		direction.setY(-1);
		velocity.setY(velocity.getY() + acceleration);		
	}
	else if (keystate[downKey])
	{
		direction.setY(1);
		velocity.setY(velocity.getY() + acceleration);		
	}
	else {//Si no se mueve en vertical frena
		velocity.setY(velocity.getY()*reductionFactor);
	}
	if (velocity.getX() > maxVelocity) {//Nunca se puede superar la velocidad máxima
		velocity.setX(maxVelocity);
	}
	if (velocity.getY() > maxVelocity) {
		velocity.setY(maxVelocity);
	}
	direction.normalize();
	getGameObject()->getTransform()->direction = direction;//Asigna la dirección	
	getGameObject()->getTransform()->velocity.setX(velocity.getX()*direction.getX());//Asigna la velocidad al personaje
	getGameObject()->getTransform()->velocity.setY(velocity.getY()*direction.getY());		
	getGameObject()->getTransform()->position.set(getGameObject()->getTransform()->position + getGameObject()->getTransform()->velocity);

}
