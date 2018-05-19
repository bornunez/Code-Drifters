#include "MCChargedAttackComponent.h"
#include "MainCharacter.h"
MCChargedAttackComponent::MCChargedAttackComponent(MainCharacter * mc) : UpdateComponent(mc)
{
	this->mc = mc;
	chargeTime.restart();
}

MCChargedAttackComponent::~MCChargedAttackComponent()
{
}

void MCChargedAttackComponent::update()
{
	
	if (mc->getCharging()) {//El timer se actualiza si el jugador está pulsando el botón de ataque
		chargeTime.update();
		if (chargeTime.TimeSinceTimerCreation > 0.2) {
			if (mc->getMCState() != MCState::ChargingAttack) {
				mc->setMCState(MCState::ChargingAttack);//Envía un mensaje para que empiece a cargar
				Message msg(ATTACKCHARGING);
				mc->sendMessage(&msg);
				chargeTime.restart();
			}
		}
	}
	else {//Si deja de pulsar, el tiempo supera al límite y está cargando entonces suelta el ataque
		if (mc->getMCState() == MCState::ChargingAttack) {
			if (mc->getCurrentAnimation()->isFinished()) {
				Message msg(ATTACKCHARGED);//Envía mensaje para que suelte el ataque
				mc->setMCState(MCState::ChargedAttack);
				mc->sendMessage(&msg);
			}
			else {
				mc->setMCState(MCState::Idle);
			}
		}
		chargeTime.restart();
	}

}

void MCChargedAttackComponent::receiveMessage(Message * msg)
{
}
