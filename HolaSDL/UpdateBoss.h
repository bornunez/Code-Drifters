#pragma once
#include "UpdateComponent.h"
#include "GameObject.h"
#include "Timer.h"
#include "MainCharacter.h"
#include "Time.h"
class UpdateBoss : public UpdateComponent
{
public:
	UpdateBoss(GameObject* o, MainCharacter* prota);
	~UpdateBoss();
protected:
	virtual void update();
private:
	GameObject* boss;
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

	Vector2D posInic;
	Vector2D posProta;
	Timer* Time;
	MainCharacter* prota;
};

