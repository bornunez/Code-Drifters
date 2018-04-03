#pragma once
#include "RenderComponent.h"
class BoxRenderer :
	public RenderComponent
{
public:
	BoxRenderer(GameObject* o, GameObject* camera);
	virtual ~BoxRenderer();
	void render();
	virtual void receiveMessage(std::string msg) {};
private:
	GameObject * camera;
	void debugBoxes();
	void debugHitbox(std::string box);
	void debugGunPosition();
};

