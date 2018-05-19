#include "WaveAnimationComponent.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"
#include "Wave.h"
#include"ResourceManager.h"

WaveAnimationComponent::WaveAnimationComponent(Wave* o, std::map<const char*, Animation*> anim, float time) : RenderComponent(o)
{
	animations = anim;
	this->ew = o;
	this->time = time;
	timer.restart();

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
			timer.restart();
		}
	}
	else {
		timer.update();
		if (timer.TimeSinceTimerCreation > time) {
			ew->setActive(false);
		}
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
