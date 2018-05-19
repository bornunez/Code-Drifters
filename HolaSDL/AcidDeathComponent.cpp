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
		float damage = 999;
		MCAttackDamage msg(damage);
		enemy->sendMessage(&msg);
	}
}

void AcidDeathComponent::update()
{
}
