#include "ChargerAnimationComponent.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"
#include "EnemyCharger.h"

ChargerAnimationComponent::ChargerAnimationComponent(GameObject* o, GameObject* target,std::map<const char*, Animation*> anim) : RenderComponent(o)
{
	animations = anim;
	gameObject->changeCurrentAnimation("RUN");
	this->target = target;
}


ChargerAnimationComponent::~ChargerAnimationComponent()
{
}

void ChargerAnimationComponent::render()
{
	handleAnimation();
	gameObject->getCurrentAnimation()->runAnimation();
}

void ChargerAnimationComponent::receiveMessage(Message * msg)
{
	if (msg->id == STALKER_RUN) {
		gameObject->changeCurrentAnimation("RUN");
		gameObject->getCurrentAnimation()->startAnimation();
	}
	else if (msg->id == STALKER_ATTACK) {
		gameObject->changeCurrentAnimation("ATTACK");
		gameObject->getCurrentAnimation()->startAnimation();
	}
}

void ChargerAnimationComponent::handleAnimation()
{
	EnemyCharger* es = static_cast<EnemyCharger*>(gameObject);
	
	if (gameObject->getCenterPos().getX() + 10 <= target->getCenterPos().getX() && es->facing == LEFTs) {		//Si está mirando a la izquierda gira
		gameObject->getCurrentAnimation()->setFlip(SDL_FLIP_HORIZONTAL);
		es->facing = RIGHTs;
	}
	else if (gameObject->getCenterPos().getX() - 10 > target->getCenterPos().getX() && es->facing == RIGHTs) {
		gameObject->getCurrentAnimation()->setFlip(SDL_FLIP_NONE);
		es->facing = LEFTs;
	}
}
