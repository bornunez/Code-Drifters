#include "BossBombAnimationComponent.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"

BossBombAnimationComponent::BossBombAnimationComponent(GameObject* o, std::map<const char*, Animation*> anim) : RenderComponent(o)
{
	animations = anim;
	gameObject->changeCurrentAnimation("BOSSBOMB");
	gameObject->getCurrentAnimation()->startAnimation();
}


BossBombAnimationComponent::~BossBombAnimationComponent()
{
}

void BossBombAnimationComponent::receiveMessage(Message * msg)
{
	switch (msg->id) {
	case ENEMY_DEATH:
		gameObject->changeCurrentAnimation("DEATH");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case ENEMY_SPAWN:
		gameObject->changeCurrentAnimation("BOSSBOMB");
		gameObject->getCurrentAnimation()->startAnimation();
	}
}

void BossBombAnimationComponent::render()
{
	gameObject->getCurrentAnimation()->runAnimation();
}




