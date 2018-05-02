#pragma once
#include "RenderComponent.h"
#include <map>
#include "Animation.h"
class EnemyBomber;
class BomberAnimationComponent : public RenderComponent
{
public:
	BomberAnimationComponent(EnemyBomber* o, GameObject* target, std::map<const char*, Animation*> anim, float hTime);
	virtual ~BomberAnimationComponent();
	void render();
	void receiveMessage(Message* msg);
	void handleAnimation();
	void hurtAnimations();
	void deathAnimations();

private:
	GameObject* target;
	EnemyBomber* eb;
	std::map<const char*, Animation*> animations;
	Timer* hurtTimer;
	float hurtTime;
};

