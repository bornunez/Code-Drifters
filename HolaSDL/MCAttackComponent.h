#pragma once
#include "InputComponent.h"
#include "Vector2D.h"
#include "Timer.h"

//Este numero define cuanto se mueve el personaje cuando ataca
const int ATTACK_MOV = 3;

class MCAttackComponent : public InputComponent
{
private:
	Vector2D aux;
	Timer* attackCD;
	enum Combo { First, Second, Third, CD };
	Combo comboAttack = First;
public:

	MCAttackComponent(GameObject* o);
	void handleEvents(SDL_Event & e);
	void receiveMessage(std::string msg) {};
	virtual ~MCAttackComponent();

};