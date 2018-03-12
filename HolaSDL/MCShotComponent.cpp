#pragma once
#include "MCShotComponent.h"
#include "Bullet.h"
#include "ResourceManager.h"
#include "Game.h"
#include "PlayState.h"
#include "MCBulletComponent.h"
#include "MCBulletRenderComponent.h"
#include "MainCharacter.h"
#include "Room.h"
#include "DungeonGenerator.h"
#include "Camera.h"
#include "PlayState.h"
#include <iostream>
MCShotComponent::MCShotComponent(GameObject * o) : InputComponent(o)
{
	lastReloadTime = new Timer();
}

MCShotComponent::~MCShotComponent()
{
}

void MCShotComponent::handleEvents(SDL_Event & e)
{
	int currentBullets = dynamic_cast<MainCharacter*>(gameObject)->getCurrentBullets();
	int reloadTime = dynamic_cast<MainCharacter*>(gameObject)->getReloadTime();//Tiempo para que se recargue una bala
	int maxBullets = dynamic_cast<MainCharacter*>(gameObject)->getMaxBullets();
	lastReloadTime->update();

	if (currentBullets == maxBullets) {//Si el cargador está al máximo la recarga se mantiene en pausa
		lastReloadTime->restart();
	}
	if (lastReloadTime->TimeSinceTimerCreation > reloadTime) {//Si el tiempo desde la última recarga supera al tiempo de recarga del personaje
		if (currentBullets < maxBullets) {//Suma una bala si el cargador no está lleno
			currentBullets++;
			dynamic_cast<MainCharacter*>(gameObject)->setCurrentBullets(currentBullets);
			lastReloadTime->restart();//Reinicia el tiempo desde la última recarga
		}
	}
	if (e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONDOWN) {
		if (currentBullets > 0) {//Si tiene balas en el cargador dispara
			int mouseX, mouseY;
			SDL_Point p;
			SDL_Rect r;
			SDL_GetMouseState(&p.x, &p.y);
			aux.setX(p.x);
			aux.setY(p.y);//Posición del cursor en pantalla

			Vector2D gunPosition = dynamic_cast<MainCharacter*>(gameObject)->getGunPosition();//Posición de donde sale la bala

																							  //cout << gunPosition << endl;

			Transform bulletTransform;
			bulletTransform.position = gunPosition;
			bulletTransform.body.w = bulletTransform.body.h = 10;


			Vector2D displayPosition;//Posición del personaje relativa a la cámara
			displayPosition = (gunPosition
				- PlayState::getInstance()->getCamera()->getTransform()->position);
			bulletTransform.direction = aux - displayPosition;//Resta la posición del cursor al del personaje
			bulletTransform.direction.normalize();//Halla el vector de dirección 

												  //Crea la bala y le pasa el transform
			Bullet* auxBullet = new Bullet(Game::getGame()->getResourceManager()->getTexture(BulletSprite), bulletTransform, true);

			//Le añade los componentes de físicas y render
			auxBullet->addComponent(new MCBulletComponent(auxBullet, 1.5));
			auxBullet->addComponent(new MCBulletRenderComponent(auxBullet));
			int currentX = PlayState::getInstance()->getMainCharacter()->getCurrentRoomX();
			int currentY = PlayState::getInstance()->getMainCharacter()->getCurrentRoomY();
			//Añade la bala a los objetos de la sala actual
			PlayState::getInstance()->getLevel()->getRoom(currentX, currentY)->addCharacter(auxBullet);

			currentBullets--;//Le resta balas al personaje
			dynamic_cast<MainCharacter*>(gameObject)->setCurrentBullets(currentBullets);
		}
	}


}

