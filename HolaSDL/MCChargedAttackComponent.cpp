#include "MCChargedAttackComponent.h"
#include "MainCharacter.h"
#include"ResourceManager.h"

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
			if (mc->getMCState() != MCState::ChargingAttack && mc->getMCState() != MCState::FullCharge) {
				ResourceManager::getInstance()->getSoundEffect(ChargingAttack)->playChannel(7, 0);
				ResourceManager::getInstance()->getSoundEffect(ChargingAttack)->changeVolume(100);
				mc->setMCState(MCState::ChargingAttack);//Envía un mensaje para que empiece a cargar
				Message msg(ATTACKCHARGING);
				mc->sendMessage(&msg);
				chargeTime.restart();
			}			
		}
		if (mc->getMCState() == MCState::ChargingAttack) {
			if (mc->getCurrentAnimation()->isFinished()) {
				Message msg(FULLCHARGE);//Envía mensaje para que suelte el ataque
				mc->setMCState(MCState::FullCharge);
				mc->sendMessage(&msg);
			}
		}
	}
	else {//Si deja de pulsar, el tiempo supera al límite y está cargando entonces suelta el ataque			

		if(mc->getMCState() == MCState::ChargingAttack){
			ResourceManager::getInstance()->getSoundEffect(ChargingAttack)->changeVolume(0);
			mc->setMCState(MCState::Idle);
		}
		else if (mc->getMCState() == MCState::FullCharge) {
			Message msg(ATTACKCHARGED);//Envía mensaje para que suelte el ataque
			mc->setMCState(MCState::ChargedAttack);
			mc->sendMessage(&msg);
			ResourceManager::getInstance()->getSoundEffect(MCSwordNormalAttack)->changeVolume(100);
			ResourceManager::getInstance()->getSoundEffect(MCSwordNormalAttack)->play();
		}
		chargeTime.restart();
	}

}

void MCChargedAttackComponent::receiveMessage(Message * msg)
{
}
