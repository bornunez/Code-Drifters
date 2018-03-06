#pragma once
#include "GunnerComponent.h"
#include "GameObject.h"
#include <cmath>

GunnerComponent::GunnerComponent(GameObject* o, GameObject* target, float vel, float dist)
{
	gameObject = o;
	type = UpdateC;
	targetObject = target;
	velocity = vel;
	distancia = dist;

}


GunnerComponent::~GunnerComponent()
{
}

void GunnerComponent::update() {

	
	gunnerPosition = getGameObject()->getTransform()->position;
	targetPosition = targetObject->getTransform()->position;
	if ((abs(targetPosition.getX() - gunnerPosition.getX()) + abs(targetPosition.getY() - gunnerPosition.getY()))
		<= distancia) {
		getGameObject()->getTransform()->velocity.set(0.0f, 0.0);
		
		//disparo si tiempo
	}
	//Regular chase
	else {
		if (gunnerPosition.getX() > targetPosition.getX()) {
			getGameObject()->getTransform()->velocity.setX(-velocity);
		}
		else getGameObject()->getTransform()->velocity.setX(velocity);

		if (gunnerPosition.getY() > targetPosition.getY()) {
			getGameObject()->getTransform()->velocity.setY(-velocity);
		}
		else getGameObject()->getTransform()->velocity.setY(velocity);
	}

	//horizontal chase
	/*else {
		if (abs(targetPosition.getX() - gunnerPosition.getX()) >= abs(targetPosition.getY() - gunnerPosition.getY())) {
			getGameObject()->getTransform()->velocity.setY(0.0f);
			if (gunnerPosition.getX() > targetPosition.getX()) {
				getGameObject()->getTransform()->velocity.setX(-velocity);
			}
			else getGameObject()->getTransform()->velocity.setX(velocity);
		
		}
		else  {
			getGameObject()->getTransform()->velocity.setX(0.0f);
			if (gunnerPosition.getY() > targetPosition.getY()) {
				getGameObject()->getTransform()->velocity.setY(-velocity);
			}
			else { getGameObject()->getTransform()->velocity.setY(velocity); }
		
		}
		
	}
	std::cout << getGameObject()->getTransform()->velocity << '\n';*/
	getGameObject()->getTransform()->position.set(gunnerPosition + getGameObject()->getTransform()->velocity);


}