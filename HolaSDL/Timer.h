#pragma once
class Timer
{
public:
	float DeltaTime = 0;
	float TimeSinceTimerCreation = 0;
	float TimeSinceGameInit = 0;
	void update();
	void restart();
	Timer();
	~Timer();

private:
	float initTime=0;
	float lastTickTime = 0;
	float tick_Time = 0;
	void Ticks();
};

