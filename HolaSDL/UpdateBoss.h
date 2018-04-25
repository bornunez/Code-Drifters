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
	void receiveMessage(Message * msg);
protected:
	virtual void update();
private:
	Vector2D direccion;
	float vel;

	GameObject* boss;
	//FASES
	void fase1();
	void fase2();
	void fase3();
	void fase4();
	void fase5();
	bool updateado = false;

	//TIEMPOS
	float tiempoAct = 0;
	float velocidad = 50;
	int faseAct = 1;
	int fasesPast = 0;
	const float tiempoFase1 = 0.7f;
	const float tiempoFase2 = 1;
	const float tiempoFase3 = 2;
	const float tiempoFase4 = 2;
	const float tiempoFase5 = 2.3;

	Vector2D posInic;
	Vector2D posProta;
	Timer* Tiempo;
	MainCharacter* prota;
};

