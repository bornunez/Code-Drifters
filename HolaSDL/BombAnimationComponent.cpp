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

void BombAnimationComponent::render()
{
	gameObject->getCurrentAnimation()->runAnimation();
}




