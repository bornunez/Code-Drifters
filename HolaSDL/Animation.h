#pragma once
#include "Texture.h"
#include "AnimationFrame.h"
#include "Timer.h"
#include <vector>
#include "GameObject.h"
class Animation
{
public:
	Animation(GameObject* o,  bool loop, float time, int frameWidth, int frameHeight);
	virtual ~Animation();
	AnimationFrame* getCurrentFrame() { return animFrames[currentFrame]; };
	AnimationFrame* getFrame(uint num) { return animFrames[num]; };
	int getNumberOfFrames() { return animFrames.size(); };
	void loadAnimation(int firstCol, int lastCol, int row, int xOffset=0, int yOffset=0);
	void loadAnimationFrame(int frameIndex, int srcRow, int srcCol, int frameWidth, int frameHeight, SDL_Rect destRect);
	void runAnimation();
	void startAnimation();
	bool isFinished();
	void setTime(int tim);
	void addAnimationFrame(SDL_Rect* srcRect, SDL_Rect destRect, int xOffset=0, int yOffset=0);
private:
	GameObject * gameObject;
	bool finish = false;;
	bool loop;
	void loopedAnimation();
	void normalAnimation();
	int currentFrame;
	float time;	
	int frameW;
	int frameH;
	Timer* lastFrame;

	std::vector<AnimationFrame*> animFrames;
};

