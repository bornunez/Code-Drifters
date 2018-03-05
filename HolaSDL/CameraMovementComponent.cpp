#pragma once
#include "CameraMovementComponent.h"
#include "MainCharacter.h"
#include "GameObject.h"
#include "Game.h"



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
	if (gameObject->getTransform()->position.getX() > gameObject->getGame()->getWorldWidth()) {
		gameObject->getTransform()->position.setX(gameObject->getGame()->getWorldWidth());
	}
	if (gameObject->getTransform()->position.getY() > gameObject->getGame()->getWorldHeight()) {
		gameObject->getTransform()->position.setY(gameObject->getGame()->getWorldHeight());
	}
}

CameraMovementComponent::~CameraMovementComponent()
{
}
