#include "StalkerAnimationComponent.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"


StalkerAnimationComponent::StalkerAnimationComponent(GameObject* o, std::map<const char*, Animation*> anim) : RenderComponent(o)
{
	animations = anim;
	gameObject->changeCurrentAnimation("RUN");
}


StalkerAnimationComponent::~StalkerAnimationComponent()
{
}

void StalkerAnimationComponent::render()
{
	gameObject->getCurrentAnimation()->runAnimation();
	
}

void StalkerAnimationComponent::receiveMessage(std::string msg)
{
	if (msg == "RUN") {
		gameObject->changeCurrentAnimation("RUN");
	}
	else if (msg == "RUN") {
		gameObject->changeCurrentAnimation("RUN");
	}
}
