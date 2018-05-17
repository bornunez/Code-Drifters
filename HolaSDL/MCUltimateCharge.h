#pragma once
//#include "checkML.h"
#include "UpdateComponent.h"
#include "Timer.h"
class MainCharacter;
class MCUltimateCharge : public UpdateComponent
{
public:
	MCUltimateCharge(MainCharacter* mc);
	void receiveMessage(Message* msg);
	void update();
	virtual ~MCUltimateCharge();
private:
	Timer * ultiCharge;//Cada x segundos, aumenta la carga de la ulti
	MainCharacter * mc;
};

