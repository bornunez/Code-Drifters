#pragma once
//#include "checkML.h"
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
#include "Wave.h"
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

	virtual void death();
	virtual void changeColor(int r, int g, int b);
	void updateEnemies();
	void renderEnemies();
	void createWave(int posX, int posY);
	vector<Wave*> returnwave() { return waves; };
	int returnWaveSize() { return waves.size(); };
private:

	RenderBoss3* rend;
	UpdateBoss3* updat;
	Vector2D posInic;
	Vector2D posProta;
	Timer* Time;
	MainCharacter* prota;
	vector<Wave*> waves;

	//RenderBoss* rend;
	//UpdateBoss* updat;
	bool epic = false; //half life change in music



	void loadAnimations();
protected:
};

