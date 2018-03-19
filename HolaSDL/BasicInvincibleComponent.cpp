#include "BasicInvincibleComponent.h"
#include "GameObject.h"


BasicInvincibleComponent::BasicInvincibleComponent(GameObject* o, float invincibleTime) : UpdateComponent(o)
{
	this->invincibleTime = invincibleTime;
	timer = new Timer();
}


BasicInvincibleComponent::~BasicInvincibleComponent()
{
}

void BasicInvincibleComponent::update()
{
	if (gameObject->getInvincibility()) {//Solo entra cuando el personaje es invencible
		timer->update();//Activa el contador, y cuando pasa el tiempo límite lo vuelve vulnerable
		if (timer->TimeSinceTimerCreation > invincibleTime) {
			gameObject->setInvincibility(false);
			timer->restart();
		}
	}
	else {
		timer->restart();
	}
}
