#pragma once
#include "RenderComponent.h"
class RenderBoss: public RenderComponent
{
public:
	virtual void render();
	void recieveMessage(std::string msg) {};
	RenderBoss(GameObject* o);
	~RenderBoss();

};

