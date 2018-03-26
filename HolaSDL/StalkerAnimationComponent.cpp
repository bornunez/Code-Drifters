#include "StalkerAnimationComponent.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"
#include "EnemyStalker.h"

StalkerAnimationComponent::StalkerAnimationComponent(GameObject* o, GameObject* target,std::map<const char*, Animation*> anim) : RenderComponent(o)
{
	animations = anim;
	gameObject->changeCurrentAnimation("RUN");
	this->target = target;
}


StalkerAnimationComponent::~StalkerAnimationComponent()
{
}

void StalkerAnimationComponent::render()
{
	handleAnimation();
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

void StalkerAnimationComponent::handleAnimation()
{
	EnemyStalker* es = static_cast<EnemyStalker*>(gameObject);
	
	if (gameObject->getCenterPos().getX() <= target->getCenterPos().getX() && es->facing==LEFT) {//Si está mirando a la izquierda gira
		gameObject->getCurrentAnimation()->setFlip(SDL_FLIP_HORIZONTAL);
		es->facing = RIGHT;
	}
	else if (gameObject->getCenterPos().getX() > target->getCenterPos().getX() && es->facing == RIGHT) {
		gameObject->getCurrentAnimation()->setFlip(SDL_FLIP_NONE);
		es->facing = LEFT;
	}
}
