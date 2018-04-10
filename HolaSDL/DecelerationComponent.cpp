#include "DecelerationComponent.h"
#include "GameObject.h"
#include "Time.h"

DecelerationComponent::DecelerationComponent(GameObject* o, float redFactor) : UpdateComponent(o) , reductionFactor(redFactor)
{
}

DecelerationComponent::~DecelerationComponent()
{
}

void DecelerationComponent::update()
{
	Transform* t = gameObject->getTransform();
	if(t->speed > 0.1)
		t->speed = t->speed - t->speed *(reductionFactor * Time::getInstance()->DeltaTime);
	if (t->speed <= 0.1){
		t->speed = 0;
		gameObject->removeComponent(this);
	}
}
