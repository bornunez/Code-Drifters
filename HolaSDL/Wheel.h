#pragma once
#include "checkML.h"
#include "GameObject.h"
#include <vector>
//#include "RenderBoss.h"
//#include "UpdateBoss.h"
#include "MasterBoss.h"
#include "AnimationParser.h"
#include "RenderWheel.h"
#include "UpdateBoss.h"
#include "SkeletonRenderer.h"
#include "PlayState.h"
#include "Enemy.h"
#include "UpdateWheel.h"
class MainCharacter;
class Timer;
class Vector2D;

class Wheel : public Enemy
{
public:
	Vector2D* centro;
	void damage(int life);
	Wheel(Transform t);
	Wheel(MainCharacter* prota, int x, int y, int w, int h, float velocidad, int dir);
	virtual ~Wheel();

	virtual void death();
	virtual void changeColor(int r, int g, int b);
	void setInvisible(bool inv);

    float GetDamage() { return Attributes.meleeDmg; };

private:

	RenderWheel* rend;
	UpdateWheel* updat;
	Vector2D posInic;
	Vector2D posProta;
	Timer* Time;
	MainCharacter* prota;
	//RenderBoss* rend;
	//UpdateBoss* updat;




	void loadAnimations();

protected:
};

