#pragma once
#include "checkML.h"
#include "RenderComponent.h"
#include <map>
#include "Animation.h"
#include "Texture.h"
#include "Timer.h"
class MainCharacter;
class MCAnimationComponent : public RenderComponent
{
public:
	MCAnimationComponent(MainCharacter* o, std::map<const char*, Animation*> anim);
	void render();
	void receiveMessage(Message* msg);
	virtual ~MCAnimationComponent();	
	void handleAnimationStates();
	void handleAnimationHook();
	void handleAnimationShot();
	void handleAnimationDash();
	void handleAnimationEndDash();
	void handleAnimationHurt();
	void handleAnimationDeath();
	void handleAnimationGun();
	void handleAnimationChargingAttack();
	void handleAnimationChargedAttack();
	float handleGunAngle();
private:
	MainCharacter * mc;
	float gunAngle = 0;
	Texture * gunTexture;
	Timer* gunTimer;
	Timer* hurtTimer;
	float hurtTime = 0.15;	//Tiempo que eres invulnerable cuando te atacan
	std::map<const char*, Animation*> animations;
	
};

