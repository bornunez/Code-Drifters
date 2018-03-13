#pragma once
#include "GameObject.h"
#include <vector>
#include "RenderBoss.h"
#include "UpdateBoss.h"
class MainCharacter;
class Timer;

class Boss : public GameObject
{
public:
	int vida = 500;
	float daño = 1;
	float tiempoAct = 0;
	float velocidad = 0.1;
	int faseAct = 1;
	float tiempoFase1 = 5;
	float tiempoFase2 = 5;

	void fase1();
	void fase2();
	void update();
	Boss(Transform t);
	Boss(MainCharacter* prota, int x, int y, int w, int h);
	~Boss();
	void render();
private:
	Vector2D posInic;
	Timer* Time;
	MainCharacter* prota;
	RenderBoss* rend;
	UpdateBoss* updat;
};

