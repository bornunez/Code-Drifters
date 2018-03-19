#include "GunnerAnimationComponent.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"


GunnerAnimationComponent::GunnerAnimationComponent(GameObject* o, std::map<const char*, Animation*> anim) : RenderComponent(o)
{
	animations = anim;
	gameObject->changeCurrentAnimation("RUN_BOT");
}


GunnerAnimationComponent::~GunnerAnimationComponent()
{
}

void GunnerAnimationComponent::render()
{
	gameObject->getCurrentAnimation()->runAnimation();

}

void GunnerAnimationComponent::recieveMessage(std::string msg)
{
	if (msg == "RUN_LEFT") {
		gameObject->changeCurrentAnimation("RUN_LEFT");
	}
	else if (msg == "RUN_RIGHT") {
		gameObject->changeCurrentAnimation("RUN_RIGHT");
	}
	else if (msg == "RUN_TOP") {
		gameObject->changeCurrentAnimation("RUN_TOP");
	}
	else if (msg == "RUN_BOT") {
		gameObject->changeCurrentAnimation("RUN_BOT");
	}
}