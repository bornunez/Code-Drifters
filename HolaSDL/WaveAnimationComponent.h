#pragma once
//#include "checkML.h"
#include "RenderComponent.h"
#include <map>
#include "Animation.h"
#include "Timer.h"
class Wave;
class WaveAnimationComponent :
	public RenderComponent
{
public:
	WaveAnimationComponent(Wave* o, std::map<const char*, Animation*> anim);
	virtual ~WaveAnimationComponent();
	void render();
	void receiveMessage(Message* msg);
private:
	Wave* ew;

	std::map<const char*, Animation*> animations;

};

