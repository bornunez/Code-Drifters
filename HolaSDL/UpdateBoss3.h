#pragma once
//#include "checkML.h"
#include "UpdateComponent.h"
#include "GameObject.h"
#include "Timer.h"
#include "MainCharacter.h"
#include "Time.h"
#include "BulletManager.h"
class Boss3;
class UpdateBoss3 : public UpdateComponent
{
public:
	UpdateBoss3(Boss3* o, MainCharacter* prota);
	virtual ~UpdateBoss3();
	void receiveMessage(Message * msg);
	void changeColor(int r, int b, int g);
protected:
	virtual void update();
private:
	Transform auxDir;
	Vector2D direccion;
	float vel;
	float velWheel = 4.75;
	int dirLucian = 1;

	Boss3* boss;
	//FASES
	void faseTP();
	void fase0();
	void fase1();
	void fase2();
	void fase3();
	void fase4();
	void fase5();
	void fase6();
	void fase7();
	void fase8();
	void fase9();
	bool updateado = false;

	void Hit();
	bool hit = false;

	void RondaWheels();
	void RondaWheels2();

	//TIEMPOS
	float tiempoAct = 0;
	float velocidad = 150;
	float tiempoRetraso = 0.3f;
	float auxVelocidad = 1;
	int faseAct = 0;
	int fasesPast = 0;
	int fasesPast0 = 0;
	float tiempoLucian = 4;
	float auxLucian = 0;
	float tiempoIntervalLucian = 0.4f;
	float auxInterval = 0;
	float auxTiempoGiro = 0.15f;
	float auxTime;
	bool para = false;

	int fasesTp = 5;
	int auxFasesTp = 0;

	float tiempoBomb = 0.75f;
	float auxBomb = 0;
	bool arriba = true;
	bool giroDir = true;
	int dir = -1;
	int auxX = 0;
	const float tiempoFaseTP = 1;
	const float tiempoFase0 = 0.5;
	const float tiempoFase1 = 2;
	const float tiempoFase2 = 2;
	const float tiempoFase3 = 6;
	const float tiempoFase4 = 20;
	const float tiempoFase5 = 7.5;
	const float tiempoFase6 = 1;
	const float tiempoFase7 = 2;
	const float tiempoFase8 = 7;
	const float tiempoFase9 = 8;

	const float timeHit = 0.1f;
	float auxTimeHit = 0;
	void auxShoot(Transform aux);

	Vector2D posInic;
	Vector2D posProta;
	Timer* Tiempo;
	MainCharacter* prota;
};

