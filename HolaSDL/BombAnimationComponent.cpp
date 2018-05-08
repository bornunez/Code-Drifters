#include "BombAnimationComponent.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"

BombAnimationComponent::BombAnimationComponent(GameObject* o, std::map<const char*, Animation*> anim) : RenderComponent(o)
{
	animations = anim;
	gameObject->changeCurrentAnimation("BOMBLOOP");
	gameObject->getCurrentAnimation()->startAnimation();
}


BombAnimationComponent::~BombAnimationComponent()
{
}

void BombAnimationComponent::receiveMessage(Message * msg)
{
	switch (msg->id) {
	case ENEMY_DEATH:
		gameObject->changeCurrentAnimation("DEATH");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case ENEMY_SPAWN:
		gameObject->changeCurrentAnimation("BOMBLOOP");
		gameObject->getCurrentAnimation()->startAnimation();
	}
}

void BombAnimationComponent::render()
{
	gameObject->getCurrentAnimation()->runAnimation();
}




