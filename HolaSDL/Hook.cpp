#include "Hook.h"
#include "ExampleRender.h"


Hook::Hook(float hookLength) : GameObject()
{
	this->hookLength = hookLength;
	addComponent(new ExampleRender(this));
	transform.body.w = 10;
	transform.body.h = 10;
	hs = STOP;
}


Hook::~Hook()
{
}
