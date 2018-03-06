#pragma once
#include "MCShotComponent.h"
#include "Bullet.h"
#include "ResourceManager.h"
#include "Game.h"
#include "PlayStateObject.h"
#include "PlayState.h"
#include "MCBulletComponent.h"
#include "MCBulletRenderComponent.h"
#include "MainCharacter.h"
#include "Room.h"
#include "DungeonGenerator.h"
#include "Camera.h"
#include <iostream>
MCShotComponent::MCShotComponent(GameObject * o)
{
	gameObject = o;
	type = InputC;
}

MCShotComponent::~MCShotComponent()
{
}

void MCShotComponent::handleEvents(SDL_Event & e)
{
	if (e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONDOWN) {

		int mouseX, mouseY;
		SDL_Point p;
		SDL_Rect r;
		SDL_GetMouseState(&p.x, &p.y);
		aux.setX(p.x);
		aux.setY(p.y);
		//Vector direccion que tendra el disparo
		
		//Se le pasa el vector
		//Ver si manejar transform como punteros mejor
		Transform bulletTransform;		
		bulletTransform.position = gameObject->getTransform()->position;
		bulletTransform.body.w = bulletTransform.body.h = 10;
		Transform displayPosition;//Posición del personaje relativa a la cámara
		displayPosition.position = (this->getGameObject()->getTransform()->position
			- dynamic_cast<MainCharacter*>(getGameObject())->getPlayState()->getCamera()->getTransform()->position);
		bulletTransform.direction = aux - displayPosition.position;//Resta la posición del cursor al del personaje
		bulletTransform.direction.normalize();//Haya el vector de dirección 
		
		//Crea la bala y le pasa el transform
		Bullet* auxBullet =new Bullet(dynamic_cast<PlayStateObject*>(gameObject)->getPlayState(),this->getGameObject()->getGame(), this->getGameObject()->getGame()->getResourceManager()->getTexture(BulletSprite), bulletTransform, true);
		
		//Le añade los componentes de físicas y render
		auxBullet->addComponent(new MCBulletComponent(auxBullet,1.5));
		auxBullet->addComponent(new MCBulletRenderComponent(auxBullet));
		int currentX = dynamic_cast<PlayStateObject*>(gameObject)->getPlayState()->getMainCharacter()->getCurrentRoomX();
		int currentY = dynamic_cast<PlayStateObject*>(gameObject)->getPlayState()->getMainCharacter()->getCurrentRoomY();
		//Añade la bala a los objetos de la sala actual
		dynamic_cast<PlayStateObject*>(gameObject)->getPlayState()->getLevel()->getRoom(currentX,currentY)->addCharacter(auxBullet);
	}


}
