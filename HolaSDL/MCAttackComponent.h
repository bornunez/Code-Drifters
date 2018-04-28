#pragma once
#include "InputComponent.h"
#include "Vector2D.h"
#include "Timer.h"

//Este numero define cuanto se mueve el personaje cuando ataca
const int ATTACK_MOV = 800;
class MainCharacter;
class MCAttackComponent : public InputComponent
{
private:
	Timer* attackCD;
	Timer* holdButton;
	enum Combo { First, Second, Third, CD };
	Combo comboAttack = First;
	MainCharacter* mc;
	bool buttonPressed = false;
public:

	MCAttackComponent(MainCharacter* mc);
	void handleEvents(SDL_Event & e);
	void receiveMessage(std::string msg) {};
	virtual ~MCAttackComponent();

};