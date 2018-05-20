#include "MCMovementInput.h"
#include "GameObject.h"
#include "MainCharacter.h"
#include "Time.h"
#include "Managers.h"
#include "Transform.h"
#include "Vector2D.h"

MCMovementInput::MCMovementInput(MainCharacter* o, SDL_Scancode up, SDL_Scancode right, SDL_Scancode down, SDL_Scancode left):
	UpdateComponent (o), upKey(up), rightKey(right), downKey(down), leftKey(left)
{
	maxVelocity = o->getMaxVelocity();//La velocidad máxima es la del personaje
	velocity.set(0, 0);
	direction.set(0, 1);//Empieza mirando hacia abajo
	mc = o;
}

MCMovementInput::~MCMovementInput()
{
}

void MCMovementInput::update()
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	SDL_PumpEvents();
	//continuous-response keys
	if (keystate[debugKey]) {
		debug = true;
	}
	Transform* t = gameObject->getTransform();
	
	//Si no hago nada Idle
	if (mc->getMCState() != MCState::Hurt &&
		mc->getMCState() != MCState::HookShot && mc->getMCState() != MCState::Attack &&
		mc->getMCState() != MCState::Dash && mc->getMCState() != MCState::Shot &&
		mc->getMCState() != MCState::DashEnd  && mc->getMCState() != MCState::Death &&
		mc->getMCState() != MCState::ChargedAttack &&
		mc->getMCState() != MCState::ChargingAttack &&
		mc->getMCState() != MCState::Ultimate
		&& mc->getMCState() != MCState::FullCharge) {

		mc->setMCState(MCState::Idle);		
	}
	//Solo puede moverse cuando está en Idle o Run
	if (mc->canMove() && (mc->getMCState() == MCState::Idle || mc->getMCState() == MCState::Run || mc->getMCState() == MCState::DashEnd || mc->getMCState() == MCState::ChargingAttack || mc->getMCState() == MCState::FullCharge)) {

		velocity.setX(0);
		velocity.setY(0);
		//La velocidad se pone a 500 cada vez que puedes moverte
		if (mc->getMCState() == MCState::ChargingAttack || mc->getMCState() == MCState::FullCharge) {
			t->speed = 50;
		}
		else t->speed = 375;

		if (keystate[leftKey])//Mueve a la izquierda
		{
			t->direction.setX(-1);
			velocity.setX(-1);
			if (mc->getMCState() != MCState::ChargingAttack && mc->getMCState() != MCState::FullCharge) mc->setMCState(MCState::Run);
			if (!keystate[upKey] && !keystate[downKey]) {//
				t->direction.setY(0);
			}
		}
		else if (keystate[rightKey])
		{
			t->direction.setX(1);
			velocity.setX(1);
			if (mc->getMCState() != MCState::ChargingAttack && mc->getMCState() != MCState::FullCharge) mc->setMCState(MCState::Run);
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
			if (mc->getMCState() != MCState::ChargingAttack && mc->getMCState() != MCState::FullCharge) mc->setMCState(MCState::Run);
			if (!keystate[leftKey] && !keystate[rightKey]) {
				t->direction.setX(0);
			}
		}
		else if (keystate[downKey])
		{
			t->direction.setY(1);
			velocity.setY(1);
			if (mc->getMCState() != MCState::ChargingAttack && mc->getMCState() != MCState::FullCharge) mc->setMCState(MCState::Run);
			if (!keystate[leftKey] && !keystate[rightKey]) {
				t->direction.setX(0);
			}
		}
		else {//Si no se mueve en vertical frena
			velocity.setY(0);
		}

		t->velocity.set(velocity);
	}
	else
		t->velocity.set(0, 0);
	
	velocity.normalize();
}

void MCMovementInput::receiveMessage(Message * msg)
{
	switch (msg->id)
	{
	case HIT_WALL:
		gameObject->getTransform()->velocity.set({ 0,0 });
		break;
	case MC_SHOT:
		gameObject->getTransform()->velocity.set({ 0,0 });
		break;
	default:
		break;
	}
}
