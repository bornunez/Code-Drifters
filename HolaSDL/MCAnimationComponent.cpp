#include "MCAnimationComponent.h"


MCAnimationComponent::MCAnimationComponent(GameObject* o) : RenderComponent(o)
{
	createAnimations();
	changeAnimation(walkLeft);
}


MCAnimationComponent::~MCAnimationComponent()
{
}
void MCAnimationComponent::recieveMessage(std::string msg) {

}
void MCAnimationComponent::render()
{

	currentAnimation->runAnimation();
}

void MCAnimationComponent::createAnimations()
{
	walkLeft = new Animation(gameObject,WALK_LEFT,8,true,0.05,108,140);
	walkLeft->loadAnimation(0,7,1);
	



	walkRight = new Animation(gameObject,WALK_RIGHT, 8,true,1,108,140);
	walkRight->loadAnimation(0,7,0);
}

void MCAnimationComponent::changeAnimation(Animation* anim)
{
	currentAnimation = anim;
	currentAnimation->startAnimation();
}
