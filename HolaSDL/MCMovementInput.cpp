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
	if (!mc->canMove()) {
		velocity.setX(0);
		velocity.setY(0);
	}
	//if(mc->canMove() && mc->getMCState() != MCState::Attack && mc->getMCState() != MCState::Dash){
	if (mc->canMove()){
		if (keystate[leftKey])
		{
			t->direction.setX(-1);
			velocity.setX(-1);
			mc->setMCState(MCState::Run);
			if (!keystate[upKey] && !keystate[downKey]) {
				t->direction.setY(0);
			}
		}
		else if (keystate[rightKey])
		{
			t->direction.setX(1);
			velocity.setX(1);
			mc->setMCState(MCState::Run);
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
			mc->setMCState(MCState::Run);
			if (!keystate[leftKey] && !keystate[rightKey]) {
				t->direction.setX(0);
			}
		}
		else if (keystate[downKey])
		{
			t->direction.setY(1);
			velocity.setY(1);
			mc->setMCState(MCState::Run);
			if (!keystate[leftKey] && !keystate[rightKey]) {
				t->direction.setX(0);
			}
		}
		else {//Si no se mueve en vertical frena
			velocity.setY(0);

		}
		if (velocity.getX() == 0 && velocity.getY() == 0 && (mc->getMCState() != MCState::HookShot && mc->getMCState() != MCState::Attack && mc->getMCState() != MCState::Dash && mc->getMCState() != MCState::Shot && mc->getMCState() != MCState::DashEnd)) {
			mc->setMCState(MCState::Idle);
		}
	}
	
	velocity.normalize();
	t->velocity.set(velocity);

}
