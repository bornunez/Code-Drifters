#pragma once
#include "GameObject.h"
#include <vector>
#include "RenderBoss.h"
#include "UpdateBoss.h"
#include "MasterBoss.h"
class MainCharacter;
class Timer;
class Vector2D;

class Boss : public MasterBoss
{
public:
	Vector2D* centro;
	void update();
	Boss(Transform t);
	Boss(MainCharacter* prota, int x, int y, int w, int h);
	~Boss();
	void render();
private:

	Vector2D posInic;
	Vector2D posProta;
	Timer* Time;
	MainCharacter* prota;
	RenderBoss* rend;
	UpdateBoss* updat;

	//FASES
	void fase1();
	void fase2();
	void fase3();
	void fase4();
	bool saltado;

	//TIEMPOS
	float tiempoAct = 0;
	float velocidad = 2.5f;
	int faseAct = 4;
	float tiempoFase1 = 5;
	float tiempoFase2 = 5;
	float tiempoFase3 = 2;
	float tiempoFase4 = 2;
};

