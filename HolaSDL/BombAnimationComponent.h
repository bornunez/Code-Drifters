#pragma once
#include "checkML.h"
#include "RenderComponent.h"
#include <map>
#include "Animation.h"
class BombAnimationComponent : public RenderComponent
{
public:
	BombAnimationComponent(GameObject* o, std::map<const char*, Animation*> anim);
	virtual ~BombAnimationComponent();
	void receiveMessage(Message* msg);

	void render();

private:
	std::map<const char*, Animation*> animations;

};

