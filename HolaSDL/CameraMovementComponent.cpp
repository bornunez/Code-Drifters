#include "CameraMovementComponent.h"
#include "MainCharacter.h"



CameraMovementComponent::CameraMovementComponent(GameObject* camera, GameObject* MCharacter )
{
	gameObject = camera;
	mainCharacter = MCharacter;
	type = UpdateC;
}

void CameraMovementComponent::update()
{
	//gameObject->getTransform()->position.setX(mainCharacter->getTransform()->position.getX());
	gameObject->getTransform()->position.setX(mainCharacter->getTransform()->position.getX() +
		mainCharacter->getTransform()->body.w / 2 -
		gameObject->getTransform()->body.w / 2);
	gameObject->getTransform()->position.setY(mainCharacter->getTransform()->position.getY() +
		mainCharacter->getTransform()->body.h / 2 -
		gameObject->getTransform()->body.h / 2);
	
	if (gameObject->getTransform()->position.getX() < 0) {
		gameObject->getTransform()->position.setX(0);
	}
	if (gameObject->getTransform()->position.getY() < 0) {
		gameObject->getTransform()->position.setY(0);
	}
	if (gameObject->getTransform()->position.getX() > 1000) {
		gameObject->getTransform()->position.setX(1000);
	}
	if (gameObject->getTransform()->position.getY() > 1000) {
		gameObject->getTransform()->position.setY(1000);
	}
}

CameraMovementComponent::~CameraMovementComponent()
{
}
