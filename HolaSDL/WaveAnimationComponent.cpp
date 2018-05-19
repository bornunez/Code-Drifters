#include "WaveAnimationComponent.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"
#include "Wave.h"
#include"ResourceManager.h"

WaveAnimationComponent::WaveAnimationComponent(Wave* o, std::map<const char*, Animation*> anim) : RenderComponent(o)
{
	animations = anim;
	this->ew = o;
	gameObject->changeCurrentAnimation("CARGA");
	gameObject->getCurrentAnimation()->startAnimation();

}


WaveAnimationComponent::~WaveAnimationComponent()
{
}

void WaveAnimationComponent::render()
{
	if (gameObject->getCurrentAnimation()->getName() == "Carga") {
		if (gameObject->getCurrentAnimation()->isFinished()) {
			gameObject->changeCurrentAnimation("EXPLOSION");
			gameObject->getCurrentAnimation()->startAnimation();
		}
	}
	else if (gameObject->getCurrentAnimation()->isFinished()) {
		
			ew->setActive(false);
			ew->setInvisible(false);
		
	}
	gameObject->getCurrentAnimation()->runAnimation();
}

void WaveAnimationComponent::receiveMessage(Message* msg)
{
	switch (msg->id) {

	case ATTACKCHARGED:
		gameObject->changeCurrentAnimation("EXPLOSION");
		gameObject->getCurrentAnimation()->startAnimation();
		break;

	}
}
