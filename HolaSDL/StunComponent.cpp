#include "StunComponent.h"
#include "Enemy.h"
#include <iostream>
#include "Animation.h"
#include "ParticlesManager.h"
#include "ResourceManager.h"
StunComponent::StunComponent(Enemy * o, float time) : UpdateComponent(o)
{
	enemy = o;
	specificTime = time;
	stunTime = 0;
}


StunComponent::~StunComponent()
{
}

void StunComponent::update()
{
	stunTimer.update();
	//Si esta stunneado, lo activamos cuando pase el tiempo de stun
	if (enemy->isStunned() && (stunTimer.TimeSinceTimerCreation > stunTime))
	{
		stunTimer.restart();
		Message msg(STUN_OFF);
		enemy->sendMessage(&msg);
		enemy->setStun(false);
	}
}

void StunComponent::receiveMessage(Message * msg)
{
	switch (msg->id)
	{
	case MC_BULLET_COLLISION: {
		if (!enemy->isDead()) {
			stunTime = static_cast<MCBulletStun*>(msg)->stunTime + specificTime;
			stunTimer.restart();
			Message msg(GUN_STUN);
			enemy->sendMessage(&msg);
			enemy->setStun(true);
			ResourceManager::getInstance()->getSoundEffect(EnemyStuned)->play();
				
			
		}
	}
	default:
		break;
	}
}
