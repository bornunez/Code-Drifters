#include "WallStunComponent.h"
#include "Enemy.h"
#include <iostream>

WallStunComponent::WallStunComponent(GameObject * o, float time) : UpdateComponent(o)
{
	enemy = static_cast<Enemy*>(gameObject);
	stunTime = time;
}


WallStunComponent::~WallStunComponent()
{
}

void WallStunComponent::update()
{
	stunTimer.update();
	//Si esta stunneado, lo activamos cuando pase el tiempo de stun
	if (enemy->isStunned() && (stunTimer.TimeSinceTimerCreation > stunTime))
	{
		stunTimer.restart();
		enemy->setStun(false);
		std::cout << "Ya no estoy stuneado" << std::endl;
	}
}

void WallStunComponent::receiveMessage(Message * msg)
{
	switch (msg->id)
	{
	case HIT_WALL: {
		if (!enemy->isStunned() && enemy->enemyState == EnemyState::Attack) {
			stunTime = 2;
			stunTimer.restart();
			enemy->setStun(true);
			std::cout << "Me reventé el cráneo contra la pared" << std::endl;
		}
	}
	default:
		break;
	}
}
