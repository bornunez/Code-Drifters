#pragma once
#include "checkML.h"
#include "RenderComponent.h"
class ExampleRender :
	public RenderComponent
{
public:
	void render();
	void receiveMessage(Message* msg) {};
	ExampleRender(GameObject* o);
	virtual ~ExampleRender();
};

