#pragma once
#include "sdl_includes.h"
class GameObject;
class AnimationFrame
{
public:
	AnimationFrame(GameObject* o,SDL_Rect* srcRect, SDL_Rect destRect);
	~AnimationFrame();
	void setHurtbox(SDL_Rect rect, int hurtboxOffsetX = 0, int hurtboxOffsetY = 0);
	void setHitbox(SDL_Rect rect,int hitboxOffsetX=0, int hitboxOffsetY=0);
	SDL_Rect getHurtbox() {	return hurtbox;	};
	SDL_Rect getHitbox() { return hitbox; };
	void render();
	void updateBoxPosition();
private:
	GameObject * gameObject;
	SDL_Rect* srcRect;
	SDL_Rect destRect;
	SDL_Rect hurtbox;
	SDL_Rect hitbox;
	int hitboxOffsetX;//La diferencia entre la posición del sprite y posición de su hitbox
	int hitboxOffsetY;
	int hurtboxOffsetX;
	int hurtboxOffsetY;
};

