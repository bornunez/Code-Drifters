#include "LastResortComponent.h"



LastResortComponent::LastResortComponent(MainCharacter* mc) : UpdateComponent(mc)
{
	character = mc;
}


LastResortComponent::~LastResortComponent()
{
}

void LastResortComponent::receiveMessage(Message* msg) {
	if (msg->id == HURT && (character->getCurrentBullets() < (float)character->getMaxBullets()/2.0) && (character->getActualHP() < character->getMaxHP()/3)) 
	{
		character->setCurrentBullets(character->getCurrentBullets() + 1);
	}
}
