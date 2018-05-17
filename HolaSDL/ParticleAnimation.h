#pragma once
//#include "checkML.h"
#include "RenderComponent.h"
#include "Timer.h"
#include "Texture.h"
class ParticleAnimation :
	public RenderComponent
{
private:
	//Puntero a la textura de la que se leen todas las animaciones
	Texture * texture;
	//Angulo de giro de la anim, si no gira es 0
	float angle;
	//Fps de la animacion, 100 serian 10 por segundo
	Uint32 fps;
	//Para voltear la animacion, por defecto no se hace
	SDL_RendererFlip flip;

	Uint32 animationNumber;
	Uint32 currentFrame = 0;
	Timer* lastFrame;
	double activeTime;
	bool loop;

	Uint32 frameW;
	Uint32 frameH;
public:
	Timer* deactivate;
	bool finish;
	ParticleAnimation(GameObject* o, Texture* texture,  double angle = 0, int fps = 100, SDL_RendererFlip flip = SDL_FLIP_NONE, bool loop = true, double time = 0);
	virtual ~ParticleAnimation();

	void render();

	//Sets
	void setAnimationNumber(Uint32 animNumber);
	void setAngle(float angle);
	void setFlip(SDL_RendererFlip flip);
	void setSize(int w, int h) { frameW = w; frameH = h; };
};

