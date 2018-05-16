#pragma once
//#include "checkML.h"
class Time
{
public:
	static Time* getInstance();
	~Time();
	float DeltaTime = 0;
	void Ticks();
private:
	Time();
	static Time* instance;
	float tick_Time = 0;
	float lastTickTime = 0;
};

