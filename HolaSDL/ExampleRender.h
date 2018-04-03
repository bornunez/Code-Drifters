#pragma once
#include "RenderComponent.h"
class ExampleRender :
	public RenderComponent
{
public:
	void render();
	void receiveMessage(std::string msg) {};
	ExampleRender(GameObject* o);
	virtual ~ExampleRender();
};

