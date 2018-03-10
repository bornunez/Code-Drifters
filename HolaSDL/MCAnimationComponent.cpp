#include "MCAnimationComponent.h"


MCAnimationComponent::MCAnimationComponent(GameObject* o) : RenderComponent(o)
{
	createAnimations();
	Play("WALK_LEFT");
}


MCAnimationComponent::~MCAnimationComponent()
{
}
void MCAnimationComponent::recieveMessage(std::string msg) {
	if (msg == "WALK_LEFT") {
		Play("WALK_LEFT");
	}
	else if(msg == "WALK_RIGHT") {
		Play("WALK_RIGHT");
	}
}
void MCAnimationComponent::render()
{

	currentAnimation->runAnimation();
}

void MCAnimationComponent::createAnimations()
{
	walkLeft = new Animation(gameObject,8,true,0.05,108,140);
	walkLeft->loadAnimation(0,7,1);

	walkRight = new Animation(gameObject, 8,true,0.05,108,140);
	walkRight->loadAnimation(0,7,0);

	animations.emplace("WALK_LEFT", walkLeft);
	animations.emplace("WALK_RIGHT", walkRight);
}

void MCAnimationComponent::Play(const char * animName)
{
	currentAnimation = animations[animName];
}

