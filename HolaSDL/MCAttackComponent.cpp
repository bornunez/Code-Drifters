#pragma once
#include "MCAttackComponent.h"
#include "ResourceManager.h"
#include "Game.h"
#include "PlayState.h"
#include "GameState.h"
#include "MCBulletComponent.h"
#include "MCBulletRenderComponent.h"
#include "MainCharacter.h"
#include "Room.h"
#include "DungeonGenerator.h"
#include "Camera.h"
#include "PlayState.h"
#include "EnemyManager.h"
#include <iostream>
#include "EnemyGunner.h"
#include "CollisionHandler.h"
MCAttackComponent::MCAttackComponent(GameObject * o) : InputComponent(o)
{
	attackCD = new Timer();
}

void MCAttackComponent::handleEvents(SDL_Event & e)
{

	if (e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONDOWN) {
		int mouseX, mouseY;
		SDL_Point p;
		SDL_Rect r;
		SDL_GetMouseState(&p.x, &p.y);
		MainCharacter* mc = static_cast<MainCharacter*>(gameObject);

		aux.setX(getGameObject()->getTransform()->position.getX() + getGameObject()->getTransform()->body.w / 2);
		aux.setY(getGameObject()->getTransform()->position.getY() + getGameObject()->getTransform()->body.h / 2);


		Vector2D displayPosition;//Posición del personaje relativa a la cámara
		displayPosition = aux - (PlayState::getInstance()->getCamera()->getTransform()->position);
		
		float angle = (atan2(p.y - displayPosition.getY() , p.x - displayPosition.getX())) ;			//Angulo entre el cursor y el jugador, en grados
		angle = angle * 180 / M_PI;
		if (angle < 0)
			angle += 360;

		mc->setActionState(Attack);

		if (angle > 210 && angle <= 270) {
			gameObject->sendMessage("ATTACK1_TOPLEFT");
			gameObject->getTransform()->direction.set(0, -1);
		}		
		else if (angle > 270 && angle < 330) {
			gameObject->sendMessage("ATTACK1_TOPRIGHT");
			gameObject->getTransform()->direction.set(0, -1);
		}
		else if (angle > 150 && angle < 210) {
			gameObject->sendMessage("ATTACK1_LEFT");
			gameObject->getTransform()->direction.set(-1, 0);
		}
		else if (angle >= 90 && angle < 150) {
			gameObject->sendMessage("ATTACK1_BOTLEFT");
			gameObject->getTransform()->direction.set(0, 1);
		}
		else if (angle > 30 && angle < 90) {
			gameObject->sendMessage("ATTACK1_BOTRIGHT");
			gameObject->getTransform()->direction.set(0, 1);
		}
		else {
			gameObject->sendMessage("ATTACK1_RIGHT");
			gameObject->getTransform()->direction.set(1, 0);
		}
	}
}

MCAttackComponent::~MCAttackComponent()
{
}
