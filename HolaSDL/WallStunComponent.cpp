#include "WallStunComponent.h"
#include "Enemy.h"

WallStunComponent::WallStunComponent(Enemy * o, float time) : UpdateComponent(o)
{
	enemy = o;
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
	}
}

void WallStunComponent::receiveMessage(Message * msg)
{
	switch (msg->id)
	{
	case HIT_WALL: {
		if (!enemy->isStunned() && enemy->enemyState == EnemyState::Attack) {
			stunTimer.restart();
			enemy->setStun(true);
		}
	}
	default:
		break;
	}
}
