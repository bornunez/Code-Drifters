#include "StalkerAnimationComponent.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"
#include "EnemyStalker.h"

StalkerAnimationComponent::StalkerAnimationComponent(EnemyStalker* o, GameObject* target,std::map<const char*, Animation*> anim) : RenderComponent(o)
{
	animations = anim;
	gameObject->changeCurrentAnimation("RUN");
	this->target = target;
	this->es = o;
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
		case HURT:
			gameObject->changeCurrentAnimation("HURT");
			gameObject->getCurrentAnimation()->startAnimation();
			break;
	}
}

void StalkerAnimationComponent::handleAnimation()
{	

	if (gameObject->getCenterPos().getX() > target->getCenterPos().getX() && es->facing == RIGHT) {//Si está mirando a la izq gira a la derecha 
		
		gameObject->flipAllAnimations(SDL_FLIP_HORIZONTAL);
		es->facing = LEFT;
		cout << "Gira Izquierda" << endl;
		
	}
	else if (gameObject->getCenterPos().getX() <= target->getCenterPos().getX() && es->facing == LEFT) {
		gameObject->flipAllAnimations(SDL_FLIP_NONE);
		es->facing = RIGHT;
	}
	
}
