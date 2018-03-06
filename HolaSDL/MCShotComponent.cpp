#pragma once
#include "MCShotComponent.h"
#include "Bullet.h"
#include "ResourceManager.h"
#include "Game.h"


void MCMovementComponent::handleEvents(SDL_Event & e)
{
	if (e.button.button == SDL_BUTTON_LEFT) {

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
		bulletTransform.direction = this->getGameObject()->getTransform()->position - aux;
		//Pasarle el transform


		new Bullet(this->getGameObject()->getGame(), this->getGameObject()->getGame()->getResourceManager()->getTexture(BulletSprite), bulletTransform, true);
	
	}


}
