#pragma once
#include "RenderComponent.h"
class ExampleRender :
	public RenderComponent
{
public:
	void render();
	void recieveMessage(std::string msg) {};
	ExampleRender(GameObject* o);
	virtual ~ExampleRender();
};

