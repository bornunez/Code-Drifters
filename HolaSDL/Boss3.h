#pragma once
#include "checkML.h"
#include "GameObject.h"
#include <vector>
//#include "RenderBoss.h"
//#include "UpdateBoss.h"
#include "MasterBoss.h"
#include "AnimationParser.h"
#include "RenderBoss3.h"
#include "UpdateBoss3.h"
#include "SkeletonRenderer.h"
#include "PlayState.h"
#include "Wheel.h"
class MainCharacter;
class Timer;
class Vector2D;

class Boss3 : public MasterBoss
{
public:
	Vector2D* centro;

	Boss3(Transform t);
	Boss3(MainCharacter* prota, int x, int y, int w, int h);
	virtual ~Boss3();

	virtual void death() {};
	virtual void changeColor(int r, int g, int b);
	void updateEnemies();
	void renderEnemies();
	void createWheel(int posX, int posY, float velocidad, int dir);
	vector<Wheel*> returnWheel() { return wheels; };
	int returnWheelSize() { return wheels.size(); };
private:

	RenderBoss3* rend;
	UpdateBoss3* updat;
	Vector2D posInic;
	Vector2D posProta;
	Timer* Time;
	MainCharacter* prota;
	vector<Wheel*> wheels;

	//RenderBoss* rend;
	//UpdateBoss* updat;




	void loadAnimations();
protected:
};

