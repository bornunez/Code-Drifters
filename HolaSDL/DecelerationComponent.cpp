#include "DecelerationComponent.h"
#include "GameObject.h"
#include "Time.h"

DecelerationComponent::DecelerationComponent(GameObject* o, float redFactor, float time) : UpdateComponent(o) , reductionFactor(redFactor), time(time)
{
	iniSpeed = gameObject->getTransform()->speed;
}

DecelerationComponent::~DecelerationComponent()
{
}

void DecelerationComponent::update()
{
	Transform* t = gameObject->getTransform();
	if (t->speed > 0.1) {
		 float aux = (iniSpeed/time) * Time::getInstance()->DeltaTime;
		 t->speed -= aux;
	}
	if (t->speed <= t->speed * (1-reductionFactor)){
		t->speed = t->speed * (1 - reductionFactor);
		gameObject->removeComponent(this);
	}
}
void DecelerationComponent::receiveMessage(Message* msg) {
	switch (msg->id)
	{
	case HIT_WALL:
	{
		Transform * t = gameObject->getTransform();
		t->speed = t->speed * (1 - reductionFactor);
		gameObject->removeComponent(this);
		break;
	}
	default:
		break;
	}
}
