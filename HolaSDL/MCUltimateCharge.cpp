#include "MCUltimateCharge.h"
#include "MainCharacter.h"


MCUltimateCharge::MCUltimateCharge(MainCharacter* mc) : UpdateComponent(mc)
{
	this->mc = mc;
	ultiCharge = new Timer();
}

void MCUltimateCharge::receiveMessage(Message * msg)
{
	switch (msg->id) {
	case ENEMY_DEATH:
		float currentUlti = mc->getUltiCharge();
		mc->setUltiCharge(currentUlti + 5);
		break;
	}
}

void MCUltimateCharge::update()
{
	ultiCharge->update();
	if (ultiCharge->TimeSinceTimerCreation > 5) {//Cada 5 segundos aumenta el valor de la ulti
		float currentUlti = mc->getUltiCharge();
		mc->setUltiCharge(currentUlti + 1);
		ultiCharge->restart();
	}
}


MCUltimateCharge::~MCUltimateCharge()
{
}
