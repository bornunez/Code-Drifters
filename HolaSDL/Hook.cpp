#include "Hook.h"
#include "ExampleRender.h"
#include "Game.h"

Hook::Hook(float hookLength) : GameObject()
{
	this->hookLength = hookLength;
	//addComponent(new ExampleRender(this));
	transform.body.w = 10 * Game::getGame()->getScale();
	transform.body.h = 10 * Game::getGame()->getScale();
	hs = STOP;
}


Hook::~Hook()
{
}
