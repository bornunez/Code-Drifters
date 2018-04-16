#pragma once
#include "MCShotComponent.h"
#include "Bullet.h"
#include "ResourceManager.h"
#include "PlayState.h"
#include "GameState.h"
#include "MCBulletComponent.h"
#include "MCBulletRenderComponent.h"
#include "MainCharacter.h"
#include "Camera.h"
#include "PlayState.h"
#include <iostream>
#include "BulletManager.h"


MCShotComponent::MCShotComponent(MainCharacter * o) : InputComponent(o), mc(o)
{
	this->bulletManager = bulletManager;
}

MCShotComponent::~MCShotComponent()
{
}

void MCShotComponent::handleEvents(SDL_Event & e)
{
	float currentBullets = mc->getCurrentBullets();
	int maxBullets = mc->getMaxBullets();

	if (e.button.button == SDL_BUTTON_RIGHT && e.type == SDL_MOUSEBUTTONDOWN) {
		if (currentBullets >= 1) {//Si tiene balas en el cargador dispara
			int mouseX, mouseY;
			SDL_Point p;
			SDL_Rect r;
			SDL_GetMouseState(&p.x, &p.y);
			aux.setX(p.x);
			aux.setY(p.y);//Posici�n del cursor en pantalla


			//Cambia la posici�n de donde sala la bala, es temporal hasta que tengamos los frames de la animaci�n definidos
			Vector2D gunPosition;
			gunPosition.setX(getGameObject()->getTransform()->position.getX() + getGameObject()->getTransform()->body.w / 2);
			gunPosition.setY(getGameObject()->getTransform()->position.getY() + getGameObject()->getTransform()->body.h / 2);
			dynamic_cast<MainCharacter*>(gameObject)->setGunPosition(gunPosition);
			
			Transform bulletTransform;
			bulletTransform.position = gunPosition;
			bulletTransform.body.w = bulletTransform.body.h = 10;


			Vector2D displayPosition;//Posici�n del personaje relativa a la c�mara
			displayPosition = (gunPosition - PlayState::getInstance()->getCamera()->getTransform()->position);
			bulletTransform.direction = aux - displayPosition;//Resta la posici�n del cursor al del personaje
			bulletTransform.direction.normalize();//Halla el vector de direcci�n 
			bulletTransform.velocity = bulletTransform.direction;
			bulletTransform.speed = 1000.0;

			BulletManager::getInstance()->shoot(this->gameObject, bulletTransform, BulletType::MCBullet);

			currentBullets -= 1;
			mc->setCurrentBullets(currentBullets); //Le resta balas al personaje
			Message msg(MC_SHOT);
			gameObject->sendMessage(&msg);
		}
	}


}
