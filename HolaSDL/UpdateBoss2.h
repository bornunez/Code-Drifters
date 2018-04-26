#pragma once
#include "UpdateComponent.h"
#include "GameObject.h"
#include "Timer.h"
#include "MainCharacter.h"
#include "Time.h"

class UpdateBoss2 : public UpdateComponent
{
public:
	UpdateBoss2(GameObject* o, MainCharacter* prota);
	~UpdateBoss2();
	void receiveMessage(Message * msg);
protected:
	virtual void update();
private:
	Vector2D direccion;
	float vel;

	GameObject* boss;
	//FASES
	void fase0();
	void fase1();
	void fase2();
	void fase3();
	void fase4();
	void fase5();
	void fase6();
	void fase7();
	bool updateado = false;

	//TIEMPOS
	float tiempoAct = 0;
	float velocidad = 0.001;
	float tiempoRetraso = 0.3f;
	float auxVelocidad = 1;
	int faseAct = 1;
	int fasesPast = 0;
	bool giroDir = true;
	const float tiempoFase0 = 2;
	const float tiempoFase1 = 2;
	const float tiempoFase2 = 2;
	const float tiempoFase3 = 1;
	const float tiempoFase4 = 2;
	const float tiempoFase5 = 1;
	const float tiempoFase6 = 1;
	const float tiempoFase7= 2;

	Vector2D posInic;
	Vector2D posProta;
	Timer* Tiempo;
	MainCharacter* prota;
};
