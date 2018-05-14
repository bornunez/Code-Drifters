#include "MCChargedAttackComponent.h"
#include "MainCharacter.h"
MCChargedAttackComponent::MCChargedAttackComponent(MainCharacter * mc, float chargeTime) : UpdateComponent(mc)
{
	this->mc = mc;
	this->chargeTime = chargeTime;
	chargeHold = new Timer();
}

MCChargedAttackComponent::~MCChargedAttackComponent()
{
}

void MCChargedAttackComponent::update()
{
	
	if (mc->getCharging()) {//El timer se actualiza si el jugador est� pulsando el bot�n de ataque
		chargeHold->update();//Actualiza el contador con el tiempo que lleva pulsado el rat�n
		//Si se lleva pulsando m�s del tiempo l�mite entonces empieza a cargar el ataque
		if (chargeHold->TimeSinceTimerCreation >= chargeTime) {
			if (mc->getMCState() != MCState::ChargingAttack) {
				mc->setMCState(MCState::ChargingAttack);//Env�a un mensaje para que empiece a cargar
				Message msg(ATTACKCHARGING);
				mc->sendMessage(&msg);
			}
			
		}
	}
	else {//Si deja de pulsar, el tiempo supera al l�mite y est� cargando entonces suelta el ataque
		if (chargeHold->TimeSinceTimerCreation >= chargeTime) {
			if (mc->getMCState() == MCState::ChargingAttack) {
				Message msg(ATTACKCHARGED);//Env�a mensaje para que suelte el ataque
				mc->setMCState(MCState::ChargedAttack);
				mc->sendMessage(&msg);
			}
		}
		chargeHold->restart();
	}

}

void MCChargedAttackComponent::receiveMessage(Message * msg)
{
}
