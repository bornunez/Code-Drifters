#include "MCUltimateCharge.h"
#include "MainCharacter.h"


MCUltimateCharge::MCUltimateCharge(MainCharacter* mc) : UpdateComponent(mc)
{
	this->mc = mc;
	ultiCharge = new Timer();
}

MCUltimateCharge::~MCUltimateCharge()
{
	delete ultiCharge;
}

void MCUltimateCharge::receiveMessage(Message * msg)
{
	switch (msg->id) {
	case ENEMY_DEATH:
		float currentUlti = mc->getUltiCharge();
		mc->setUltiCharge(currentUlti + (5.0/ mc->getUltiBonusCD()));
		break;
	}
}

void MCUltimateCharge::update()
{
	ultiCharge->update();
	if (ultiCharge->TimeSinceTimerCreation > 1) {//Cada segundo aumenta el valor de la ulti
		float currentUlti = mc->getUltiCharge();
		mc->setUltiCharge(currentUlti + (0.2/mc->getUltiBonusCD()));
		ultiCharge->restart();
	}
}



