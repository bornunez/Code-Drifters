#pragma once
#include "checkML.h"
#include "RenderComponent.h"
#include "Texture.h"
#include "Timer.h"
class MainCharacter;
class Hook;
enum AnimationNumber { FirstAnim, SecondAnim, ThirdAnim };
class HookAnimationComponent :
	public RenderComponent
{
public:
	HookAnimationComponent(Hook* o, Texture* hookChainTex, Texture* hookChainFailTex, Texture* hookHeadTex, double angle = 0, int fps = 100, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void receiveMessage(Message * msg);
	void render();
	void renderHookHead();
	void renderHookChains();
	void renderHookFail();
	virtual ~HookAnimationComponent();
	void setAngle(float angle);
	void setFlip(SDL_RendererFlip flip);
	float getSpriteAngle(Vector2D origin, Vector2D target);

	AnimationNumber animationNumber;
private:
	Hook * hook;
	Timer* hookFailAnim;
	Uint32 hookFailSprite=0;
	bool stopAnim = false;
	//Puntero a la textura de la que se leen todas las animaciones
	Texture* hookChainTex;
	Texture* hookHeadTex;
	Texture* hookChainFailTex;
	//Angulo de giro de la anim, si no gira es 0
	float angle;
	//Fps de la animacion, 100 serian 10 por segundo
	int fps;
	//Para voltear la animacion, por defecto no se hace
	SDL_RendererFlip flip;
};

