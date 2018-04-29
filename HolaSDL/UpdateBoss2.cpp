#include "UpdateBoss2.h"
#include "Boss2.h"


UpdateBoss2::UpdateBoss2(GameObject* o, MainCharacter* prot) : UpdateComponent(o)
{
	boss = o;
	Tiempo = new Timer();
	prota = prot;
	posInic = Vector2D(boss->getTransform()->position.getX(), boss->getTransform()->position.getY());
}


UpdateBoss2::~UpdateBoss2()
{
}
void UpdateBoss2::receiveMessage(Message * msg)
{
	switch (msg->id) {
	case HURT:
		break;
	case MC_ATTACK_DAMAGE:
		break;
	}
}
void UpdateBoss2::changeColor(int r, int g, int b)
{
	boss->getCurrentAnimation()->changeColor(r, g, b);
	auxTimeHit = 0;
	hit = true;
}

void UpdateBoss2::Hit()
{
	if (auxTimeHit >= timeHit)
	{
		hit = false;
		boss->getCurrentAnimation()->changeColor(255, 255, 255);
	}
	else auxTimeHit += Time::getInstance()->DeltaTime;
}

void UpdateBoss2::update()
{
	boss->allUpdates();
	updateado = false;
	static_cast<Boss2*>(boss)->updateEnemies();
	//cout << auxVelocidad;
	if (faseAct == 0 && (Tiempo->TimeSinceTimerCreation < tiempoFase0) && !updateado)
	{
		fase0();
	}
	else if (faseAct == 0 && !updateado)
	{
		Tiempo->restart();
		faseAct = 1;
		updateado = true;
	}
	if (faseAct == 1 && (Tiempo->TimeSinceTimerCreation < tiempoFase1) && !updateado)
	{
		fase1();
	}
	else if (faseAct == 1 && !updateado)
	{
		Tiempo->restart();
		faseAct = 2;
		updateado = true;
	}
	if (faseAct == 2 && Tiempo->TimeSinceTimerCreation < tiempoFase2 && !updateado)
	{
		fase2();
	}
	else if (faseAct == 2 && !updateado)
	{
		Tiempo->restart();
		faseAct = 3;
		updateado = true;
	}
	if (faseAct == 3 && Tiempo->TimeSinceTimerCreation < tiempoFase3 && !updateado)
	{
		fase3();
	}
	else if (faseAct == 3 && !updateado)
	{
		Tiempo->restart();
		faseAct = 4;
		updateado = true;
	}
	if (faseAct == 4 && Tiempo->TimeSinceTimerCreation < tiempoFase4 && !updateado)
	{
		fase4();
	}
	else if (faseAct == 4 && !updateado)
	{
		Tiempo->restart();
		faseAct = 5;
		updateado = true;
	}
	if (faseAct == 5 && Tiempo->TimeSinceTimerCreation < tiempoFase5 && !updateado)
	{
		fase5();
	}
	else if (faseAct == 5 && !updateado)
	{
		Tiempo->restart();
		faseAct = 6;
		updateado = true;
	}
	if (faseAct == 6 && Tiempo->TimeSinceTimerCreation < tiempoFase6 && !updateado)
	{
		fase6();
	}
	else if (faseAct == 6 && !updateado)
	{
		Tiempo->restart();
		faseAct = 7;
		updateado = true;
	}
	if (faseAct == 7 && Tiempo->TimeSinceTimerCreation < tiempoFase7 && !updateado)
	{
		fase7();
	}
	else if (faseAct == 7 && !updateado)
	{
		Tiempo->restart();
		faseAct = 0;
		updateado = true;
	}

	if (hit) Hit();
	Tiempo->update();
}



void UpdateBoss2::fase0()
{
	if (Tiempo->TimeSinceTimerCreation == 0)
	{
		boss->changeCurrentAnimation("STATIC_DOWN");
		boss->getCurrentAnimation()->startAnimation();
		RondaWheels();
		fasesPast = 1;
		//static_cast<Boss2*>(boss)->createWheel(boss->getTransform()->position.getX() + 300, boss->getTransform()->position.getY());
	}
	else if (Tiempo->TimeSinceTimerCreation > tiempoFase0/4 && fasesPast == 1)
	{
		RondaWheels();
		fasesPast = 2;
	}
	else if (Tiempo->TimeSinceTimerCreation > tiempoFase0 / 2.5 && fasesPast == 2)
	{
		RondaWheels();
		fasesPast = 3;
	}
	else if (Tiempo->TimeSinceTimerCreation > tiempoFase0 / 1.5 && fasesPast == 3)
	{
		RondaWheels();
		fasesPast = 0;
	}
}
void UpdateBoss2::fase1()
{
	if (Tiempo->TimeSinceTimerCreation == 0)
	{
		boss->changeCurrentAnimation("SALE");
		boss->getCurrentAnimation()->startAnimation();
	}
}

void UpdateBoss2::fase2()
{
	if (Tiempo->TimeSinceTimerCreation == 0)
	{
		boss->changeCurrentAnimation("WARNING");
		boss->getCurrentAnimation()->startAnimation();
	}
}
void UpdateBoss2::fase3()
{
	if (Tiempo->TimeSinceTimerCreation == 0)
	{
		boss->changeCurrentAnimation("SACA_RAYOS");
		boss->getCurrentAnimation()->setTime(0.1);
		boss->getCurrentAnimation()->startAnimation();
	}
}

void UpdateBoss2::fase4()
{
	if (Tiempo->TimeSinceTimerCreation == 0)
	{
		boss->changeCurrentAnimation("GIRA");
		boss->getCurrentAnimation()->startAnimation();

		auxVelocidad = 0.3f;
		giroDir = true;
	}
	if(auxVelocidad > velocidad && giroDir)
	auxVelocidad -= Time::getInstance()->DeltaTime;
	else if(giroDir)
	{
		auxVelocidad = velocidad;
		tiempoRetraso = 0.3f;
		giroDir = false;
	}
	if (tiempoRetraso > 0) tiempoRetraso -= Time::getInstance()->DeltaTime;
	if (!giroDir && tiempoRetraso <= 0)
	{
		auxVelocidad += Time::getInstance()->DeltaTime / 2;
	}
	boss->getCurrentAnimation()->setTime(auxVelocidad);
}
void UpdateBoss2::fase5()
{
	if (Tiempo->TimeSinceTimerCreation == 0)
	{
		boss->changeCurrentAnimation("SACA_RAYOS");
		boss->getCurrentAnimation()->setTime(-0.1);
		boss->getCurrentAnimation()->startAnimation();

	}
}
void UpdateBoss2::fase6()
{
	if (Tiempo->TimeSinceTimerCreation == 0)
	{
		boss->changeCurrentAnimation("WARNING");
		boss->getCurrentAnimation()->startAnimation();
	}
}
void UpdateBoss2::fase7()
{
	if (Tiempo->TimeSinceTimerCreation == 0)
	{
		boss->changeCurrentAnimation("ENTRA");
		boss->getCurrentAnimation()->startAnimation();
	}
}

void UpdateBoss2::RondaWheels()
{
	dirWheel = Random::randomInt(0, 3);
	if (dirWheel == 0)
	{
		int salto = Random::randomInt(0, 7);
		if (salto != 0)static_cast<Boss2*>(boss)->createWheel(625, 550, velWheel, dirWheel);
		if (salto != 1)static_cast<Boss2*>(boss)->createWheel(625, 675, velWheel, dirWheel);
		if (salto != 2)static_cast<Boss2*>(boss)->createWheel(625, 800, velWheel, dirWheel);
		if (salto != 3)static_cast<Boss2*>(boss)->createWheel(625, 925, velWheel, dirWheel);
		if (salto != 4)static_cast<Boss2*>(boss)->createWheel(625, 1050, velWheel, dirWheel);
		if (salto != 5)static_cast<Boss2*>(boss)->createWheel(625, 1175, velWheel, dirWheel);
		if (salto != 6)static_cast<Boss2*>(boss)->createWheel(625, 1300, velWheel, dirWheel);
		if (salto != 7)static_cast<Boss2*>(boss)->createWheel(625, 1425, velWheel, dirWheel);
	}
	else if (dirWheel == 1)
	{
		int salto = Random::randomInt(0, 7);
		if (salto != 0)static_cast<Boss2*>(boss)->createWheel(625, 550, velWheel, dirWheel);
		if (salto != 1)static_cast<Boss2*>(boss)->createWheel(775, 550, velWheel, dirWheel);
		if (salto != 2)static_cast<Boss2*>(boss)->createWheel(925, 550, velWheel, dirWheel);
		if (salto != 3)static_cast<Boss2*>(boss)->createWheel(1075, 550, velWheel, dirWheel);
		if (salto != 4)static_cast<Boss2*>(boss)->createWheel(1225, 550, velWheel, dirWheel);
		if (salto != 5)static_cast<Boss2*>(boss)->createWheel(1375, 550, velWheel, dirWheel);
		if (salto != 6)static_cast<Boss2*>(boss)->createWheel(1525, 550, velWheel, dirWheel);
		if (salto != 7)static_cast<Boss2*>(boss)->createWheel(1675, 550, velWheel, dirWheel);
	}
	else if (dirWheel == 2)
	{
		int salto = Random::randomInt(0, 7);
		if (salto != 0)static_cast<Boss2*>(boss)->createWheel(1675, 550, velWheel, dirWheel);
		if (salto != 1)static_cast<Boss2*>(boss)->createWheel(1675, 675, velWheel, dirWheel);
		if (salto != 2)static_cast<Boss2*>(boss)->createWheel(1675, 800, velWheel, dirWheel);
		if (salto != 3)static_cast<Boss2*>(boss)->createWheel(1675, 925, velWheel, dirWheel);
		if (salto != 4)static_cast<Boss2*>(boss)->createWheel(1675, 1050, velWheel, dirWheel);
		if (salto != 5)static_cast<Boss2*>(boss)->createWheel(1675, 1175, velWheel, dirWheel);
		if (salto != 6)static_cast<Boss2*>(boss)->createWheel(1675, 1300, velWheel, dirWheel);
		if (salto != 7)static_cast<Boss2*>(boss)->createWheel(1675, 1425, velWheel, dirWheel);
	}
	else if (dirWheel == 3)
	{
		int salto = Random::randomInt(0, 7);
		if (salto != 0)static_cast<Boss2*>(boss)->createWheel(625, 1425, velWheel, dirWheel);
		if (salto != 1)static_cast<Boss2*>(boss)->createWheel(775, 1425, velWheel, dirWheel);
		if (salto != 2)static_cast<Boss2*>(boss)->createWheel(925, 1425, velWheel, dirWheel);
		if (salto != 3)static_cast<Boss2*>(boss)->createWheel(1075, 1425, velWheel, dirWheel);
		if (salto != 4)static_cast<Boss2*>(boss)->createWheel(1225, 1425, velWheel, dirWheel);
		if (salto != 5)static_cast<Boss2*>(boss)->createWheel(1375, 1425, velWheel, dirWheel);
		if (salto != 6)static_cast<Boss2*>(boss)->createWheel(1525, 1425, velWheel, dirWheel);
		if (salto != 7)static_cast<Boss2*>(boss)->createWheel(1675, 1425, velWheel, dirWheel);
	}
}
