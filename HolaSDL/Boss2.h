#pragma once
#include "GameObject.h"
#include <vector>
//#include "RenderBoss.h"
//#include "UpdateBoss.h"
#include "MasterBoss.h"
#include "AnimationParser.h"
#include "RenderBoss2.h"
#include "UpdateBoss2.h"
#include "SkeletonRenderer.h"
#include "PlayState.h"
class MainCharacter;
class Timer;
class Vector2D;

class Boss2 : public MasterBoss
{
public:
	Vector2D* centro;

	Boss2(Transform t);
	Boss2(MainCharacter* prota, int x, int y, int w, int h);
	~Boss2();

	virtual void death() {};
private:

	RenderBoss2* rend;
	UpdateBoss2* updat;
	Vector2D posInic;
	Vector2D posProta;
	Timer* Time;
	MainCharacter* prota;
	//RenderBoss* rend;
	//UpdateBoss* updat;





	void loadAnimations();
protected:
};

