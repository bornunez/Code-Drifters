#include "MCMovementInput.h"
#include "GameObject.h"
#include "MainCharacter.h"
#include "Time.h"
#include "Managers.h"
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
	MainCharacter* mc = static_cast<MainCharacter*>(gameObject);
	SDL_PumpEvents();
	//continuous-response keys
	if (keystate[debugKey]) {
		debug = true;
	}
	Transform* t = gameObject->getTransform();
	if (mc->getActionState() == Attack) {
		velocity.setX(0);
		velocity.setY(0);
	}
	else {
		if (keystate[leftKey])
		{
			t->direction.setX(-1);
			velocity.setX(-1);
			mc->setActionState(Run);
			if (!keystate[upKey] && !keystate[downKey]) {
				t->direction.setY(0);
			}
		}
		else if (keystate[rightKey])
		{
			t->direction.setX(1);
			velocity.setX(1);
			mc->setActionState(Run);
			if (!keystate[upKey] && !keystate[downKey]) {
				t->direction.setY(0);
			}
		}
		else {//Si no se mueve en horizontal entonces frena
			velocity.setX(0);

		}
		if (keystate[upKey])
		{
			t->direction.setY(-1);
			velocity.setY(-1);
			mc->setActionState(Run);
			if (!keystate[leftKey] && !keystate[rightKey]) {
				t->direction.setX(0);
			}
		}
		else if (keystate[downKey])
		{
			t->direction.setY(1);
			velocity.setY(1);
			mc->setActionState(Run);
			if (!keystate[leftKey] && !keystate[rightKey]) {
				t->direction.setX(0);
			}
		}
		else {//Si no se mueve en vertical frena
			velocity.setY(0);

		}
		if (velocity.getX() == 0 && velocity.getY() == 0 && mc->getActionState() != Attack) {
			mc->setActionState(Idle);
		}
	}
	
	
	
	velocity.normalize();
	t->velocity.set(velocity);
	if (debug) {

		/*
		system("cls");
		cout << "Player info: \nPosition: [ X: " << t->position.getX() << " ,Y: " << t->position.getY() << " ]" << endl;
		cout << "Velocity: [ X: " << t->velocity.getX() << " ,Y: " << t->velocity.getY() << " ]" << endl;
		cout << "Direction: [ X: " << t->direction.getX() << " ,Y: " << t->direction.getY() << " ]" << endl;
		cout << "Body: [ X: " << t->body.x << " ,Y: " << t->body.y << " ,W: " << t->body.w << " H: " << t->body.h << " ]" << endl;
		cout << "CenterPosition: [ X: " << gameObject->getCenterPos().getX() << " ,Y: " << gameObject->getCenterPos().getY() << " ]" << endl;
		cout << "DisplayPosition: [ X: " << gameObject->getDisplayPos().getX() << " ,Y: " << gameObject->getDisplayPos().getY() << " ]" << endl;*/
	}	
}
