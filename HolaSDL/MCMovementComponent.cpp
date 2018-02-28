#include "MCMovementComponent.h"
#include "GameObject.h"
#include <iostream>


MCMovementComponent::MCMovementComponent(GameObject* o, SDL_Keycode up, SDL_Keycode right, SDL_Keycode down, SDL_Keycode left) :
	upKey(up), rightKey(right), downKey(down), leftKey(left)
{
	gameObject = o;
	type = InputC;
}
void MCMovementComponent::handleEvents(SDL_Event & e)
{
	//Vector2D velocity = gameObject->getVelocity();
	Vector2D velocity = getGameObject()->getTransform()->velocity;
	
	if (e.type == SDL_KEYDOWN) {
	
		if (e.key.keysym.sym == upKey) {
			velocity.setY(-5);
		}
		else if (e.key.keysym.sym == downKey) {
			velocity.setY(5);
		}
		if (e.key.keysym.sym == rightKey) {
			velocity.setX(5);
		}
		else if (e.key.keysym.sym == leftKey) {
			velocity.setX(-5);
		}
	}

	getGameObject()->getTransform()->velocity = velocity;//Se mueve, esto debería ir en las físicas
	getGameObject()->getTransform()->position.set(getGameObject()->getTransform()->position + getGameObject()->getTransform()->velocity);
	getGameObject()->getTransform()->velocity.set(0,0);
}



MCMovementComponent::~MCMovementComponent()
{
}
