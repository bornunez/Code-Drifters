#include "AcidDeathComponent.h"

#include "Enemy.h"

AcidDeathComponent::AcidDeathComponent(Enemy* e) : UpdateComponent(e)
{
	enemy = e;
}


AcidDeathComponent::~AcidDeathComponent()
{
}

void AcidDeathComponent::receiveMessage(Message * msg)
{
	if (msg->id == ACID_DEATH) {
		enemy->death();
	}
}

void AcidDeathComponent::update()
{
}
