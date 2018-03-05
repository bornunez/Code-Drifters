#pragma once
#include "GameObject.h"

class MainCharacter;

class Boss : public GameObject
{
public:
	int vida = 500;
	float daño = 1;
	float tiempoAct = 0;
	float velocidad = 0.1;
	//int fase[];
	void fase1();
	void update();
	Boss(Game* game, Transform t);
	Boss(Game* game, MainCharacter* prota, int x, int y, int w, int h);
	~Boss();
	void render();
private:
	MainCharacter* prota;
};

