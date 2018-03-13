#include "MCMovementInput.h"
#include "GameObject.h"
#include "MainCharacter.h"
MCMovementInput::MCMovementInput(GameObject * o, SDL_Scancode up, SDL_Scancode right, SDL_Scancode down, SDL_Scancode left): 
	UpdateComponent (o), upKey(up), rightKey(right), downKey(down), leftKey(left)
{
	maxVelocity = dynamic_cast<MainCharacter*>(gameObject)->getMaxVelocity();//La velocidad máxima es la del personaje
	velocity.set(0, 0);
	direction.set(0, 1);//Empieza mirando hacia abajo
}

MCMovementInput::~MCMovementInput()
{
}

void MCMovementInput::update()
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	SDL_PumpEvents();
	//continuous-response keys
	debug = keystate[debugKey];
	if (keystate[leftKey])
	{
		direction.setX(-1);
		velocity.setX(maxVelocity);
		gameObject->sendMessage("RUN_LEFT");
	}
	else if (keystate[rightKey])
	{
		direction.setX(1);
		velocity.setX(maxVelocity);
		gameObject->sendMessage("RUN_RIGHT");
	}
	else {//Si no se mueve en horizontal entonces frena
		velocity.setX(0);
	}
	if (keystate[upKey])
	{
		direction.setY(-1);
		velocity.setY(maxVelocity);
		gameObject->sendMessage("RUN_TOP");
	}
	else if (keystate[downKey])
	{
		direction.setY(1);
		velocity.setY(maxVelocity);
		gameObject->sendMessage("RUN_BOT");
	}
	else {//Si no se mueve en vertical frena
		velocity.setY(0);
	}

	Transform* t = gameObject->getTransform();
	t->velocity.set(velocity);
	t->direction.set(direction);
}
