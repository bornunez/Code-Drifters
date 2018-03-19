#pragma once
#include "RenderComponent.h"
#include "Vector2D.h"
class RenderBoss: public RenderComponent
{
public:
	virtual void render();
	void recieveMessage(std::string msg) {};
	RenderBoss(GameObject* o, Vector2D* pos);
	~RenderBoss();

private:
	Vector2D* posicion;
};

