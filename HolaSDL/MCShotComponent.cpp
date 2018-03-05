#include "MCShotComponent.h"
#include "Bullet.h"


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


	/*	Transform bulletTransform = { this->getGameObject()->getTransform()->position }
		{
			Vector2D position;
			Vector2D rotation;
			Vector2D velocity;
			Vector2D direction;
			SDL_Rect body;
		};*/
		//Pasarle el transform

		new Bullet(this->getGameObject()->getGame());
	}


}
