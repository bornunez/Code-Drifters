#pragma once
#include "RenderComponent.h"
#include "Texture.h"

enum AnimationNumber {FirstAnim, SecondAnim, ThirdAnim};
class Timer;
class SimpleAnimationComponent : public RenderComponent
{
private:
	//Puntero a la textura de la que se leen todas las animaciones
	Texture* texture;
	//Angulo de giro de la anim, si no gira es 0
	float angle;
	//Fps de la animacion, 100 serian 10 por segundo
	int fps;
	//Para voltear la animacion, por defecto no se hace
	SDL_RendererFlip flip;

	AnimationNumber animationNumber;
	Uint32 currentFrame = 0;
	Timer* lastFrame;
	bool loop;
	bool finish;

	int frameW;
	int frameH;

public:
	SimpleAnimationComponent(GameObject* o, Texture* texture, double angle = 0, int fps = 100, SDL_RendererFlip flip = SDL_FLIP_NONE, bool loop = true);
	~SimpleAnimationComponent();
	void render();

	//Sets
	void setAnimationNumber(AnimationNumber animNumber);
	void setAngle(float angle);
	void setFlip(SDL_RendererFlip flip);
	void setSize(int w, int h) { frameW = w; frameH = h; };
};

