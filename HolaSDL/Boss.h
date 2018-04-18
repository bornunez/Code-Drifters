#pragma once
#include "GameObject.h"
#include <vector>
//#include "RenderBoss.h"
//#include "UpdateBoss.h"
#include "MasterBoss.h"
#include "AnimationParser.h"
#include "RenderBoss.h"
#include "UpdateBoss.h"
class MainCharacter;
class Timer;
class Vector2D;

class Boss : public MasterBoss
{
public:
	Vector2D* centro;

	Boss(Transform t);
	Boss(MainCharacter* prota, int x, int y, int w, int h);
	~Boss();

private:

	RenderBoss* rend;
	UpdateBoss* updat;
	Vector2D posInic;
	Vector2D posProta;
	Timer* Time;
	MainCharacter* prota;
	//RenderBoss* rend;
	//UpdateBoss* updat;

	//FASES
	void fase1();
	void fase2();
	void fase3();
	void fase4();
	bool saltado;

	//TIEMPOS
	float tiempoAct = 0;
	float velocidad = 2.5f;
	int faseAct = 1;
	float tiempoFase1 = 5;
	float tiempoFase2 = 5;
	float tiempoFase3 = 2;
	float tiempoFase4 = 2;

	void loadAnimations();
protected:
	virtual void update();
    virtual void render();
};

