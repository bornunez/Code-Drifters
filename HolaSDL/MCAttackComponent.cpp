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
	attackCD->update();
	if ((attackCD->TimeSinceTimerCreation >= 0.4 && comboAttack == Second) ||  //Si te pasas el tiempo disponible para realizar el segundo ataque
		(attackCD->TimeSinceTimerCreation >= 0.75)) {   //Si te pasas el tiempo disponible para realizar el tercer ataque

		attackCD->restart();
		comboAttack = First;
		static_cast<MainCharacter*>(gameObject)->setActionState(Idle);		//La animacion vuelve a idle
	}


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

		//attackCD->update();

		if (comboAttack == First)
			attackCD->restart();



		//if(attackCD->TimeSinceTimerCreation >= 1) {
	//		attackCD->restart();
		//	comboAttack = First;
	//	}
		//	else if (attackCD->TimeSinceTimerCreation >= 1 && comboAttack == First) {					//Si el tiempo ha superado el maximo el timer del combo vuelve a 0
		//	attackCD->restart();
		//	comboAttack = First;
		//	}

		Message msg(NO_ID);

		if (attackCD->TimeSinceTimerCreation == 0 && comboAttack == First) {
			//Pasa el estado a atacando
			mc->setActionState(Attack);

			if (angle > 210 && angle <= 270) {
				msg.id = ATTACK1_TOPLEFT;
				gameObject->getTransform()->direction.set(-1, -1);
			}
			else if (angle > 270 && angle < 330) {
				msg.id = ATTACK1_TOPRIGHT;
				gameObject->getTransform()->direction.set(1, -1);
			}
			else if (angle > 150 && angle < 210) {
				msg.id = ATTACK1_LEFT;
				gameObject->getTransform()->direction.set(-1, 0);
			}
			else if (angle >= 90 && angle < 150) {
				msg.id = ATTACK1_BOTLEFT;
				gameObject->getTransform()->direction.set(-1, 1);
			}
			else if (angle > 30 && angle < 90) {
				msg.id = ATTACK1_BOTRIGHT;
				gameObject->sendMessage(&msg);
				gameObject->getTransform()->direction.set(1, 1);
			}
			else {
				msg.id = ATTACK1_RIGHT;
				gameObject->getTransform()->direction.set(1, 0);
			}
			comboAttack = Second;
		}
		else if (attackCD->TimeSinceTimerCreation >= 0.25 && comboAttack == Second) {
			//Pasa el estado a atacando
			mc->setActionState(Attack);

			if (angle > 210 && angle <= 270) {
				msg.id = ATTACK2_TOPLEFT;
				gameObject->getTransform()->direction.set(0, -1);
			}
			else if (angle > 270 && angle < 330) {
				msg.id = ATTACK2_TOPRIGHT;
				gameObject->getTransform()->direction.set(0, -1);
			}
			else if (angle > 150 && angle < 210) {
				msg.id = ATTACK2_LEFT;
				gameObject->getTransform()->direction.set(-1, 0);
			}
			else if (angle >= 90 && angle < 150) {
				msg.id = ATTACK2_BOTLEFT;
				gameObject->getTransform()->direction.set(0, 1);
			}
			else if (angle > 30 && angle < 90) {
				msg.id = ATTACK2_BOTRIGHT;
				gameObject->getTransform()->direction.set(0, 1);
			}
			else {
				msg.id = ATTACK2_RIGHT;
				gameObject->getTransform()->direction.set(1, 0);
			}
			comboAttack = Third;
		}
		else if (attackCD->TimeSinceTimerCreation >= 0.5 && comboAttack == Third) {
			//Pasa el estado a atacando
			mc->setActionState(Attack);

			if (angle > 210 && angle <= 270) {
				msg.id = ATTACK3_TOPLEFT;
				gameObject->getTransform()->direction.set(0, -1);
			}
			else if (angle > 270 && angle < 330) {
				msg.id = ATTACK3_RIGHT;
				gameObject->getTransform()->direction.set(0, -1);
			}
			else if (angle > 150 && angle < 210) {
				msg.id = ATTACK3_LEFT;
				gameObject->getTransform()->direction.set(-1, 0);
			}
			else if (angle >= 90 && angle < 150) {
				msg.id = ATTACK3_BOTLEFT;
				gameObject->getTransform()->direction.set(0, 1);
			}
			else if (angle > 30 && angle < 90) {
				msg.id = ATTACK3_BOTRIGHT;
				gameObject->getTransform()->direction.set(0, 1);
			}
			else {
				msg.id = ATTACK3_RIGHT;
				gameObject->getTransform()->direction.set(1, 0);
			}
			comboAttack = CD;
			attackCD->restart();
		}

		//Se envia el mensaje 
		gameObject->sendMessage(&msg);
	}
}

MCAttackComponent::~MCAttackComponent()
{
}
