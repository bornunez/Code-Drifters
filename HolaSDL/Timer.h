#pragma once
//#include "checkML.h"
class Timer
{
public:
	Timer();
	~Timer();
	float TimeSinceGameInit = 0;
	float TimeSinceTimerCreation = 0;
	void update();
	void restart();

private:
	float initTime = 0;
};
