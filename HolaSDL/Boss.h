#pragma once
#include "checkML.h"
#include "GameObject.h"
#include <vector>
//#include "RenderBoss.h"
//#include "UpdateBoss.h"
#include "MasterBoss.h"
#include "AnimationParser.h"
#include "RenderBoss.h"
#include "UpdateBoss.h"
#include "SkeletonRenderer.h"
#include "PlayState.h"
class MainCharacter;
class Timer;
class Vector2D;

class Boss : public MasterBoss
{
public:
	Vector2D* centro;
	void damage(int life);
	Boss(Transform t);
	Boss(MainCharacter* prota, int x, int y, int w, int h);
	virtual ~Boss();

	virtual void death();
	virtual void changeColor(int r, int g, int b);

private:

	RenderBoss* rend;
	UpdateBoss* updat;
	Vector2D posInic;
	Vector2D posProta;
	Timer* Time;
	MainCharacter* prota;
	//RenderBoss* rend;
	//UpdateBoss* updat;




	void loadAnimations();

protected:
};

