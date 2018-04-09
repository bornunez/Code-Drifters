#include "Hook.h"
#include "ExampleRender.h"


Hook::Hook(float hookLength) : GameObject()
{
	this->hookLength = hookLength;
	//addComponent(new ExampleRender(this));
	transform.body.w = 20;
	transform.body.h = 20;
	hs = STOP;
}


Hook::~Hook()
{
}
