#pragma once
//#include "checkML.h"
#include "RenderComponent.h"
#include <map>
#include "Animation.h"
class BossBombAnimationComponent : public RenderComponent
{
public:
	BossBombAnimationComponent(GameObject* o, std::map<const char*, Animation*> anim);
	virtual ~BossBombAnimationComponent();
	void receiveMessage(Message* msg);

	void render();

private:
	std::map<const char*, Animation*> animations;

};

