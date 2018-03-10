#include "Animation.h"



Animation::Animation(GameObject* o,AnimationID id, int totalFrames, bool loop, float time, int frameWidth, int framwHeight)
{
	gameObject = o;
	this->time = time;
	this->loop = loop;
	this->totalFrames = totalFrames;
	frameW = frameWidth;
	frameH = framwHeight;
	currentFrame = 0;
	lastFrame = new Timer();
}


Animation::~Animation()
{
}

void Animation::loopedAnimation()
{
	
	if (lastFrame->TimeSinceTimerCreation > time) {
		lastFrame->restart();
		//animFrames[currentFrame]->render();
		currentFrame++;
		if (currentFrame >= animFrames.size()) {
			currentFrame = 0;
		}
	}
	animFrames[currentFrame]->render();
}

void Animation::normalAnimation()
{
	if (lastFrame->TimeSinceTimerCreation > time) {
		lastFrame->restart();
		//animFrames[currentFrame]->render();
		currentFrame++;
		if (currentFrame >= animFrames.size()) {
			currentFrame = animFrames.size()-1;
		}
	}
	animFrames[currentFrame]->render();
}

void Animation::loadAnimation(int firstRow, int lastRow, int col)
{
	for (int i = firstRow; i < lastRow; i++) {
		SDL_Rect* aux = new SDL_Rect();
		aux->h = frameH;
		aux->w = frameW;
		aux->x = frameW * firstRow;
		aux->y = frameH * col;
		aux->x = frameW * i;
		addAnimationFrame(aux, gameObject->getTransform()->body);
	}
}

void Animation::startAnimation()
{
	currentFrame = 0;
}

void Animation::runAnimation()
{
	lastFrame->update();
	if (loop) {
		loopedAnimation();
	}
	else {
		normalAnimation();
	}
}

void Animation::setTime(int tim)
{
	time = tim;
}

void Animation::addAnimationFrame(SDL_Rect* srcRect, SDL_Rect destRect)
{
	AnimationFrame* aux = new AnimationFrame(gameObject,srcRect,destRect);
	animFrames.push_back(aux);
}
