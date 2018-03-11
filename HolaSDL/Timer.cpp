#include "Timer.h"
#include "sdl_includes.h"
#include <iostream>


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
	Ticks();
	TimeSinceGameInit = float(SDL_GetTicks())/1000;
	TimeSinceTimerCreation = (float(SDL_GetTicks()) - initTime)/1000;
}

void Timer::restart()
{
	TimeSinceTimerCreation = 0;
	initTime = SDL_GetTicks();
}

void Timer::Ticks()
{
	tick_Time = SDL_GetTicks();
	DeltaTime = (tick_Time - lastTickTime)/1000;
	lastTickTime = tick_Time;
}
