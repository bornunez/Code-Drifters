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
#include "Time.h"

MCAttackComponent::MCAttackComponent(MainCharacter * mc) : InputComponent(static_cast<GameObject*>(mc))
{
	//ResetAttack y AttackDelay
	this->mc = mc;
	attackCD = new Timer();
}

void MCAttackComponent::handleEvents(SDL_Event & e)
{

	if(mc->getMCState()== MCState::Attack || mc->getMCState() == MCState::Idle || comboAttack == CD)
		attackCD->update();

	if (attackCD->TimeSinceTimerCreation >= 0.5 || (mc->getMCState() == MCState::Attack && gameObject->getCurrentAnimation()->isFinished())) {
		attackCD->restart();
		comboAttack = First;
		mc->setMCState(MCState::Idle);		//La animacion vuelve a idle		
	}



	if (e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONDOWN) {
		if (mc->getMCState() == MCState::Idle || mc->getMCState() == MCState::Run || mc->getMCState() == MCState::DashEnd || mc->getMCState() == MCState::Attack) {
			
			mc->setCharging(true);//Booleano que indica que está cargando el ataque

			int mouseX, mouseY;
			SDL_Point p;
			SDL_Rect r;
			SDL_GetMouseState(&p.x, &p.y);

			Vector2D displayPosition;			//Posición del personaje relativa a la cámara
			displayPosition = mc->getDisplayCenterPos();
			float angle = (atan2(p.y - displayPosition.getY(), p.x - displayPosition.getX()));			//Angulo entre el cursor y el jugador, en grados
			angle = angle * 180 / M_PI;
			if (angle < 0)
				angle += 360;
		
			displayPosition = (mc->getTransform()->position - PlayState::getInstance()->getCamera()->getTransform()->position);

			Transform* t = mc->getTransform();

			// Si no estas en CD te mueves al atacar
			if (comboAttack != CD) {
				t->direction.set(p.x - displayPosition.getX(), p.y - displayPosition.getY());//Resta la posición del cursor al del personaje

				t->direction.normalize();													//Halla el vector de dirección 
				Vector2D aux = t->direction * ATTACK_MOV;									//Multiplica por cuanto debe moverse
				t->position.set(t->position + aux * (min((float)1, Time::getInstance()->DeltaTime)));
				t->velocity.set({ 0,0 });

			}
			if (comboAttack == First)
				attackCD->restart();


			Message msg(NO_ID);

			if (attackCD->TimeSinceTimerCreation == 0 && comboAttack == First) {
				//Pasa el estado a atacando
				mc->setMCState(MCState::Attack);

				if (angle > 210 && angle <= 270) {
					msg.id = ATTACK1_TOPLEFT;
					t->direction.set(0, -1);
				}
				else if (angle > 270 && angle < 330) {
					msg.id = ATTACK1_TOPRIGHT;
					t->direction.set(0, -1);
				}
				else if (angle > 150 && angle < 210) {
					msg.id = ATTACK1_LEFT;
					t->direction.set(-1, 0);
				}
				else if (angle >= 90 && angle < 150) {
					msg.id = ATTACK1_BOTLEFT;
					t->direction.set(0, 1);
				}
				else if (angle > 30 && angle < 90) {
					msg.id = ATTACK1_BOTRIGHT;
					t->direction.set(0, 1);
				}
				else {
					msg.id = ATTACK1_RIGHT;
					t->direction.set(1, 0);
				}
				comboAttack = Second;
			}
			//else if (attackCD->TimeSinceTimerCreation >= 0.25 && comboAttack == Second) {
			else if (comboAttack == Second) {
				attackCD->restart();
				//Pasa el estado a atacando
				mc->setMCState(MCState::Attack);

				if (angle > 210 && angle <= 270) {
					msg.id = ATTACK2_TOPLEFT;
					t->direction.set(0, -1);
				}
				else if (angle > 270 && angle < 330) {
					msg.id = ATTACK2_TOPRIGHT;
					t->direction.set(0, -1);
				}
				else if (angle > 150 && angle < 210) {
					msg.id = ATTACK2_LEFT;
					t->direction.set(-1, 0);
				}
				else if (angle >= 90 && angle < 150) {
					msg.id = ATTACK2_BOTLEFT;
					t->direction.set(0, 1);
				}
				else if (angle > 30 && angle < 90) {
					msg.id = ATTACK2_BOTRIGHT;
					t->direction.set(0, 1);
				}
				else {
					msg.id = ATTACK2_RIGHT;
					t->direction.set(1, 0);
				}
				comboAttack = Third;
			}
			//else if (attackCD->TimeSinceTimerCreation >= 0.5 && comboAttack == Third) {
			else if (comboAttack == Third) {
				attackCD->restart();
				//Pasa el estado a atacando
				mc->setMCState(MCState::Attack);

				if (angle > 210 && angle <= 270) {
					msg.id = ATTACK3_TOPLEFT;
					t->direction.set(0, -1);
				}
				else if (angle > 270 && angle < 330) {
					msg.id = ATTACK3_TOPRIGHT;
					t->direction.set(0, -1);
				}
				else if (angle > 150 && angle < 210) {
					msg.id = ATTACK3_LEFT;
					t->direction.set(-1, 0);
				}
				else if (angle >= 90 && angle < 150) {
					msg.id = ATTACK3_BOTLEFT;
					t->direction.set(0, 1);
				}
				else if (angle > 30 && angle < 90) {
					msg.id = ATTACK3_BOTRIGHT;
					t->direction.set(0, 1);
				}
				else {
					msg.id = ATTACK3_RIGHT;
					t->direction.set(1, 0);
				}
				//Poniendo aqui First haces ataques sin pausa
				comboAttack = CD;
				attackCD->restart();
			}			
			//Se envia el mensaje 
			gameObject->sendMessage(&msg);
			ResourceManager::getInstance()->getSoundEffect(MCSwordNormalAttack)->play();
		}
		
	}
	else if(e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONUP) {
		mc->setCharging(false);
		
	}	
}

MCAttackComponent::~MCAttackComponent()
{
}
