#pragma once
#include "sdl_includes.h"
#include <vector>
class GameObject;
class Tileset;
class AnimationFrame
{
public:
	AnimationFrame(Tileset* tileset, GameObject* o,SDL_Rect* srcRect, SDL_Rect destRect, int frameOffsetX=0, int frameOffsetY=0);
	~AnimationFrame();
	void addHurtbox(SDL_Rect rect, int offsetX=0, int offsetY=0);
	void addHitbox(SDL_Rect rect, int offsetX=0, int offsetY=0);
	std::vector<SDL_Rect> getHurtboxes() {	return hurtboxes;};
	std::vector<SDL_Rect> getHitboxes() { return hitboxes; };
	void render();
	void updateBoxPosition();
private:
	Tileset * tileSet;
	GameObject * gameObject;
	SDL_Rect* srcRect;
	SDL_Rect destRect;
	std::vector<SDL_Rect> hurtboxes;
	std::vector<SDL_Rect> hitboxes;
	std::vector<std::pair<int, int>> hurtboxOffset;//Vector que contiene los offset de las hurtboxes	
	std::vector<std::pair<int, int>> hitboxOffset;
	
	int frameOffsetX;
	int frameOffsetY;
};

