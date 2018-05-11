#include "Time.h"
#include "sdl_includes.h"


Time* Time::instance = nullptr;

Time* Time::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Time();
	}
	return instance;
}

Time::Time()
{
}


Time::~Time()
{
}

void Time::Ticks()
{
	tick_Time = SDL_GetTicks();
	DeltaTime = fmin((tick_Time - lastTickTime) / 1000,0.5);
	lastTickTime = tick_Time;
}
