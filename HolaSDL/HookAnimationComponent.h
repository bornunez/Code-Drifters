#pragma once
#include "RenderComponent.h"
#include "Texture.h"
class Hook;
enum AnimationNumber { FirstAnim, SecondAnim, ThirdAnim };
class HookAnimationComponent :
	public RenderComponent
{
public:
	HookAnimationComponent(Hook* o, Texture* hookChainTex, Texture* hookHeadTex,double angle = 0, int fps = 100, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void receiveMessage(std::string msg) {};
	void render();
	void renderHookHead();
	void renderHookChains();
	virtual ~HookAnimationComponent();
	void setAngle(float angle);
	void setFlip(SDL_RendererFlip flip);

	AnimationNumber animationNumber;
private:
	Hook * hook;
	//Puntero a la textura de la que se leen todas las animaciones
	Texture* hookChainTex;
	Texture* hookHeadTex;
	//Angulo de giro de la anim, si no gira es 0
	float angle;
	//Fps de la animacion, 100 serian 10 por segundo
	int fps;
	//Para voltear la animacion, por defecto no se hace
	SDL_RendererFlip flip;
};

