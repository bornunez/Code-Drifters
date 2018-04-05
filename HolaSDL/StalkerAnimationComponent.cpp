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

void StalkerAnimationComponent::receiveMessage(Message* msg)
{
	switch (msg->id) {
		case STALKER_RUN:
			gameObject->changeCurrentAnimation("RUN");
			gameObject->getCurrentAnimation()->startAnimation();
			break;
		case STALKER_ATTACK:
			gameObject->changeCurrentAnimation("ATTACK");
			gameObject->getCurrentAnimation()->startAnimation();
			break;
	}
}

void StalkerAnimationComponent::handleAnimation()
{
	EnemyStalker* es = static_cast<EnemyStalker*>(gameObject);
	
	if (gameObject->getCenterPos().getX() + 10 <= target->getCenterPos().getX() && es->facing == LEFT) {		//Si está mirando a la izquierda gira
		gameObject->getCurrentAnimation()->setFlip(SDL_FLIP_HORIZONTAL);
		es->facing = RIGHT;
	}
	else if (gameObject->getCenterPos().getX() - 10 > target->getCenterPos().getX() && es->facing == RIGHT) {
		gameObject->getCurrentAnimation()->setFlip(SDL_FLIP_NONE);
		es->facing = LEFT;
	}
}
