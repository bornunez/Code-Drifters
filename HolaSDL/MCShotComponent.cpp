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
		this->getGameObject()->getTransform()->position - aux;
		//Se le pasa el vector
		//Ver si manejar transform como punteros mejor
		Transform bulletTransform = (*this->getGameObject()->getTransform());
		bulletTransform.body.w = bulletTransform.body.h = 10;
		bulletTransform.direction = this->getGameObject()->getTransform()->position - aux;
		
		//Pasarle el transform
		
		Bullet* auxBullet =new Bullet(dynamic_cast<PlayStateObject*>(gameObject)->getPlayState(),this->getGameObject()->getGame(), this->getGameObject()->getGame()->getResourceManager()->getTexture(BulletSprite), bulletTransform, true);
		
		auxBullet->addComponent(new MCBulletComponent(auxBullet,0.001));
		auxBullet->addComponent(new MCBulletRenderComponent(auxBullet));
		int currentX = dynamic_cast<PlayStateObject*>(gameObject)->getPlayState()->getMainCharacter()->getCurrentRoomX();
		int currentY = dynamic_cast<PlayStateObject*>(gameObject)->getPlayState()->getMainCharacter()->getCurrentRoomY();
		dynamic_cast<PlayStateObject*>(gameObject)->getPlayState()->getLevel()->getRoom(currentX,currentY)->addCharacter(auxBullet);
	}


}
