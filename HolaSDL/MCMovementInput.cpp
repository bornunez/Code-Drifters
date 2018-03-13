#include "MCMovementInput.h"
#include "GameObject.h"
#include "MainCharacter.h"
#include "Time.h"
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
	debug = keystate[debugKey];
	if (keystate[leftKey])
	{
		direction.setX(-1);
		velocity.setX(-1);
		gameObject->sendMessage("RUN_LEFT");
		mc->setActionState(Run);
	}
	else if (keystate[rightKey])
	{
		direction.setX(1);
		velocity.setX(1);
		gameObject->sendMessage("RUN_RIGHT");
		mc->setActionState(Run);
	}
	else {//Si no se mueve en horizontal entonces frena
		velocity.setX(0);
		direction.setX(0);
	}
	if (keystate[upKey])
	{
		direction.setY(-1);
		velocity.setY(-1);
		gameObject->sendMessage("RUN_TOP");
		mc->setActionState(Run);
	}
	else if (keystate[downKey])
	{
		direction.setY(1);
		velocity.setY(1);
		gameObject->sendMessage("RUN_BOT");
		mc->setActionState(Run);
	}
	else {//Si no se mueve en vertical frena
		velocity.setY(0);
		direction.setX(0);
	}
	if (velocity.getX() == 0 && velocity.getY() == 0) {
		mc->setActionState(Idle);
	}
	if (!keystate[upKey] && !keystate[downKey] && !keystate[rightKey] && !keystate[leftKey] && mc->getActionState()==Idle) {
		if (direction.getX() == 1 && direction.getY() == 0) {//Derecha
			gameObject->sendMessage("IDLE_RIGHT");
		}
		else if (direction.getX() == -1 && direction.getY() == 0) {//Izquierda
			gameObject->sendMessage("IDLE_LEFT");
		}
		else if (direction.getX() == 0 && direction.getY() == 1) {//Abajo
			gameObject->sendMessage("IDLE_BOT");
		}
		else if (direction.getX() == 0 && direction.getY() == -1) {//Arriba
			gameObject->sendMessage("IDLE_TOP");
		}
	}

	Transform* t = gameObject->getTransform();
	velocity.normalize();
	t->velocity.set(velocity);
	t->direction.set(direction);
	if (debug) {
		system("cls");
		cout << "Player info: \nPosition: [ X: " << t->position.getX() << " ,Y: " << t->position.getY() << " ]" << endl;
		cout << "Velocity: [ X: " << t->velocity.getX() << " ,Y: " << t->velocity.getY() << " ]" << endl;
		cout << "Direction: [ X: " << t->direction.getX() << " ,Y: " << t->direction.getY() << " ]" << endl;
		cout << "Body: [ X: " << t->body.x << " ,Y: " << t->body.y << " ,W: " << t->body.w << " H: " << t->body.h << " ]" << endl;
	}
}
