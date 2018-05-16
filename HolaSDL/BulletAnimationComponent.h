#pragma once
//#include "checkML.h"
#include "RenderComponent.h"
#include "Texture.h"
class Bullet;
class BulletAnimationComponent : public RenderComponent
{
public:
	BulletAnimationComponent(Bullet* o, Texture* texture, double angle = 0, int fps = 100, SDL_RendererFlip flip = SDL_FLIP_NONE);
	virtual ~BulletAnimationComponent();
	void render();
	void receiveMessage(Message * msg);
	float getSpriteAngle();
	//Puntero a la textura de la que se leen todas las animaciones
	Texture* texture;
	//Angulo de giro de la anim, si no gira es 0
	float angle;
	//Fps de la animacion, 100 serian 10 por segundo
	int fps;
	//Para voltear la animacion, por defecto no se hace
	SDL_RendererFlip flip;
	Bullet* bullet;
};

