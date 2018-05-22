#pragma once
//#include "checkML.h"
#include "Time.h"
class Timer
{
public:
	Timer();
	~Timer();
	float TimeSinceGameInit = 0;
	float TimeSinceTimerCreation = 0;
	float lastTime = 0;
	void update();
	void restart();

private:
	float initTime = 0;
};
