#include "MCMovementComponent.h"
#include "GameObject.h"


MCMovementComponent::MCMovementComponent(SDL_Keycode up, SDL_Keycode right, SDL_Keycode down, SDL_Keycode left) :
	upKey(up), rightKey(right), downKey(down), leftKey(left)
{
}
void MCMovementComponent::handleEvents(SDL_Event & e)
{
	//Vector2D velocity = gameObject->getVelocity();
	
	Vector2D velocity = getGameObject()->getTransform()->velocity;
	
	if (e.type == SDL_KEYDOWN) {
		if (e.key.keysym.sym == upKey) {
			velocity = velocity + Vector2D(0, -2);
		}
		else if (e.key.keysym.sym == rightKey) {
			velocity = velocity + Vector2D(2, 0);
		}
		else if (e.key.keysym.sym == downKey) {
			//velocity.set(0, 0);
		}
		else if (e.key.keysym.sym == leftKey) {

		}
	}

	getGameObject()->getTransform()->velocity = velocity;
}



MCMovementComponent::~MCMovementComponent()
{
}
