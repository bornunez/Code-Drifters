#pragma once
//#include "checkML.h"
#include "GameObject.h"
#include <vector>
#include "MasterBoss.h"
#include "AnimationParser.h"
#include "WaveAnimationComponent.h"
#include "SkeletonRenderer.h"
#include "PlayState.h"
#include "Enemy.h"
class MainCharacter;
class Timer;
class Vector2D;

class Wave : public Enemy
{
public:
	Vector2D* centro;
	Wave(Transform t);
	Wave(MainCharacter* prota, int x, int y, int w, int h);
	virtual ~Wave();

	void setInvisible(bool inv);

    float GetDamage() { return Attributes.meleeDmg; };

private:

	WaveAnimationComponent* rend;
	Vector2D posInic;
	Vector2D posProta;
	MainCharacter* prota;
	void loadAnimations();

};

