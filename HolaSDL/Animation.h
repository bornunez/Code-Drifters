#pragma once
#include "Texture.h"
#include "AnimationFrame.h"
#include "Timer.h"
#include <vector>
#include "GameObject.h"
enum AnimationID { WALK_RIGHT, WALK_LEFT, WALK_DOWN, WALK_UP, ATTACK_LEFT, ATTACK_RIGHT, ATTACK_DOWN, ATTACK_UP };
class Animation
{
public:
	Animation(GameObject* o,AnimationID id, int totalFrames, bool loop, float time, int frameWidth, int frameHeight);
	virtual ~Animation();
	int getCurrentFrame() { return currentFrame; };
	void loadAnimation(int firstRow, int lastRow, int col);
	void startAnimation();
	void runAnimation();
	void setTime(int tim);
	void addAnimationFrame(SDL_Rect* srcRect, SDL_Rect destRect);
private:
	GameObject * gameObject;
	bool loop;
	void loopedAnimation();
	void normalAnimation();
	AnimationID ID;
	int currentFrame;
	float time;	
	int totalFrames;
	int frameW;
	int frameH;
	Timer* lastFrame;
	std::vector<AnimationFrame*> animFrames;
};

