#pragma once
#include "checkML.h"
#include "UpdateComponent.h"
class MainCharacter;
class MCGunPosition :
	public UpdateComponent
{
public:
	MCGunPosition(MainCharacter* mc);
	virtual ~MCGunPosition();
	void update();
	void receiveMessage(std::string msg) {};
	float handleGunAngle();
private:
	MainCharacter * mc;
};

