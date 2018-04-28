#pragma once
#include "UpdateComponent.h"
#include "GameObject.h"
#include "Timer.h"
#include "MainCharacter.h"
#include "Time.h"
#include "Vector2D.h"
class UpdateWheel : public UpdateComponent
{
public:
	UpdateWheel(GameObject* o, MainCharacter* prota);
	~UpdateWheel();
	void receiveMessage(Message * msg);
	void changeColor(int r, int b, int g);
protected:
	virtual void update();
private:
	Vector2D direccion;
	Vector2D posProta;
	Vector2D posInic;
	float vel;

	void fase1();
	void fase2();
	void fase3();

	const float tiempoFase1 = 2;
	const float tiempoFase2 = 2;
	const float tiempoFase3 = 1;

	//TIEMPOS
	float tiempoAct = 0;
	float velocidad = 0.001;
	float tiempoRetraso = 0.3f;
	float auxVelocidad = 1;
	int faseAct = 1;
	int fasesPast = 0;


	bool updateado = false;
	GameObject* wheel;
	Timer* tiempo;
	MainCharacter* prota;
};