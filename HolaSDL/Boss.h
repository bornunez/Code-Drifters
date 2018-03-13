#pragma once
#include "GameObject.h"
#include <vector>

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
	Boss(Game* game, Transform t);
	Boss(Game* game, MainCharacter* prota, int x, int y, int w, int h);
	~Boss();
	void render();
private:
	Vector2D posInic;
	Timer* Time;
	MainCharacter* prota;
};

