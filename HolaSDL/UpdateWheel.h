#pragma once
#include "UpdateComponent.h"
#include "GameObject.h"
#include "Timer.h"
#include "MainCharacter.h"
#include "Time.h"
#include "Vector2D.h"
#include "Random.h"
class Wheel;
class UpdateWheel : public UpdateComponent
{
public:
	UpdateWheel(Wheel* o, MainCharacter* prota, float velocidad, int dir);
	~UpdateWheel();
	void receiveMessage(Message * msg);
	void changeColor(int r, int b, int g);
protected:
	virtual void update();
private:
	Vector2D direccion;
	Vector2D posProta;
	int posInic;
	int dir;
	float vel = 2;

	void fase1();
	void fase2();
	void fase3();

	const float tiempoFase1 = 2.5f;
	const float tiempoFase2 = 4.85f;
	const float tiempoFase3 = 1.25f;

	//TIEMPOS
	float tiempoAct = 0;
	float velocidad = 0.001;
	float tiempoRetraso = 0.3f;
	float auxVelocidad = 1;
	int faseAct = 1;
	int fasesPast = 0;


	bool updateado = false;
	Wheel* wheel;
	Timer* tiempo;
	MainCharacter* prota;
	GameObject* boss;
};