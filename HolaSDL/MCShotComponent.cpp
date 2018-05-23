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
	mc = o;
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
			if (mc->getMCState() == MCState::Idle || mc->getMCState() == MCState::Run || mc->getMCState() == MCState::DashEnd) {
				int mouseX, mouseY;
				SDL_Point p;
				SDL_Rect r;
				SDL_GetMouseState(&p.x, &p.y);
				aux.setX(p.x);
				aux.setY(p.y);//Posición del cursor en pantalla


				//Cambia la posición de donde sala la bala, es temporal hasta que tengamos los frames de la animación definidos
				Vector2D gunPosition = mc->getGunPosition();

				Transform bulletTransform;
				bulletTransform.body.w = bulletTransform.body.h = 10;
				bulletTransform.position = gunPosition + PlayState::getInstance()->getCamera()->getTransform()->position;
				bulletTransform.position.setX(bulletTransform.position.getX() - bulletTransform.body.w / 2);
				bulletTransform.position.setY(bulletTransform.position.getY() - bulletTransform.body.h / 2);

				Vector2D displayPosition;//Posición del personaje relativa a la cámara
				displayPosition = (gunPosition);
				bulletTransform.direction = aux - displayPosition;//Resta la posición del cursor al del personaje
				bulletTransform.direction.normalize();//Halla el vector de dirección 
				bulletTransform.velocity = bulletTransform.direction;
				bulletTransform.speed = 2000.0;

				BulletManager::getInstance()->shoot(this->gameObject, bulletTransform, BulletType::MCBullet);

				/*bulletTransform.direction.rotate(15);
				bulletTransform.velocity.rotate(15);
				BulletManager::getInstance()->shoot(this->gameObject, bulletTransform, BulletType::MCBullet);

				bulletTransform.direction.rotate(-30);
				bulletTransform.velocity.rotate(-30);
				BulletManager::getInstance()->shoot(this->gameObject, bulletTransform, BulletType::MCBullet);*/

				currentBullets -= 1;
				mc->setCurrentBullets(currentBullets); //Le resta balas al personaje
				Message msg(MC_SHOT);
				gameObject->sendMessage(&msg);

				ResourceManager::getInstance()->getSoundEffect(MCGunShot)->changeVolume(50);
				ResourceManager::getInstance()->getSoundEffect(MCGunShot)->play();
			}
		}
	}


}
