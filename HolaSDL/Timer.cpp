#include "sdl_includes.h"
#include <iostream>
#include "Timer.h"


using namespace std;

Timer::Timer()
{
	initTime = SDL_GetTicks();
}

Timer::~Timer()
{
}

void Timer::update()
{
	TimeSinceGameInit = float(SDL_GetTicks())/1000;
	TimeSinceTimerCreation = (float(SDL_GetTicks()) - initTime)/1000;
	if (TimeSinceTimerCreation - lastTime > 1) TimeSinceTimerCreation = lastTime+Time::getInstance()->DeltaTime;
	lastTime = TimeSinceTimerCreation;
}


void Timer::restart()
{
	TimeSinceTimerCreation = 0;
	initTime = SDL_GetTicks();
}


