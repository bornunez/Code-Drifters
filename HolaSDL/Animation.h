#pragma once
#include "Texture.h"
#include "AnimationFrame.h"
#include "Timer.h"

#include <vector>
#include "GameObject.h"
class TileLayer;
class Layer;
class Tileset;
class Animation
{
public:
	Animation(string animationName, Tileset* tileset, GameObject* o, int tileSize, int offsetx=0, int offsety=0, bool loop = true, float time = 0.05 );
	virtual ~Animation();
	AnimationFrame* getCurrentFrame() { return animFrames[currentFrame]; };
	AnimationFrame* getFrame(uint num) { return animFrames[num]; };
	int getNumberOfFrames() { return animFrames.size(); };
	void runAnimation();
	void startAnimation();
	bool isFinished();
	void setTime(float tim);
	void addAnimationFrame(SDL_Rect* srcRect, SDL_Rect destRect, int xOffset=0, int yOffset=0, int frameWidth=64, int frameHeight=64);
	void setLayer(TileLayer* lay);
	TileLayer* getLayer() { return layer; };
	string getName() { return name; };
	void setFlip(SDL_RendererFlip flip);
	int getFrameWidth() { return frameW; };
	int getFrameHeight() { return frameH; };
private:
	TileLayer* layer;
	Tileset* tileSet;
	GameObject * gameObject;
	bool finish = false;;
	bool loop;
	bool inverted = false;
	void loopedAnimation();
	void normalAnimation();
	int currentFrame;
	float time;	
	int frameW;
	int frameH;
	int offsetX;
	int offsetY;
	Timer* lastFrame;
	string name;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	std::vector<AnimationFrame*> animFrames;
};

