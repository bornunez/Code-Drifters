#pragma once
#include "CameraMovementComponent.h"
#include "MainCharacter.h"
#include "GameObject.h"
#include "Game.h"



CameraMovementComponent::CameraMovementComponent(GameObject* camera, GameObject* MCharacter ) : UpdateComponent(camera)
{
	mainCharacter = MCharacter;
	lastPos = mainCharacter->getTransform()->position;
	offset = Game::getGame()->getScale();
}

void CameraMovementComponent::update()
{
	
		//gameObject->getTransform()->position.setX(mainCharacter->getTransform()->position.getX());
		lastPos = mainCharacter->getTransform()->position;
		gameObject->getTransform()->position.setX(mainCharacter->getTransform()->body.x +
			mainCharacter->getTransform()->body.w / 2 -
			gameObject->getTransform()->body.w / 2);
		gameObject->getTransform()->position.setY(mainCharacter->getTransform()->body.y +
			mainCharacter->getTransform()->body.h / 2 -
			gameObject->getTransform()->body.h / 2);
	
		if (gameObject->getTransform()->position.getX() < 0) {
			gameObject->getTransform()->position.setX(0);
		}
		if (gameObject->getTransform()->position.getY() < 0) {
			gameObject->getTransform()->position.setY(0);
		}
		if (gameObject->getTransform()->position.getX() > Game::getGame()->getWorldWidth()) {
			gameObject->getTransform()->position.setX(Game::getGame()->getWorldWidth());
		}
		if (gameObject->getTransform()->position.getY() > Game::getGame()->getWorldHeight()) {
			gameObject->getTransform()->position.setY(Game::getGame()->getWorldHeight());
		}

	
}

CameraMovementComponent::~CameraMovementComponent()
{
}
