#pragma once
#include "sdl_includes.h"
class GameObject;
class AnimationFrame
{
public:
	AnimationFrame(GameObject* o,SDL_Rect* srcRect, SDL_Rect destRect);
	~AnimationFrame();
	void setHurtbox(SDL_Rect rect);
	void setHitbox(SDL_Rect rect);
	SDL_Rect getHurtbox() {	return hurtbox;	};
	SDL_Rect getHitbox() { return hitbox; };
	void render();
private:
	GameObject * gameObject;
	SDL_Rect* srcRect;
	SDL_Rect destRect;
	SDL_Rect hurtbox;
	SDL_Rect hitbox;
};

