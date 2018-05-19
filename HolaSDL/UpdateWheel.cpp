#include "UpdateWheel.h"
#include "Wheel.h"
#include "EnemyManager.h"


UpdateWheel::UpdateWheel(Wheel* o, MainCharacter* prot, float velocidad, int direccion) : UpdateComponent(o)
{
	dir = direccion;
	wheel = o;
	prota = prot;
	tiempo = new Timer();
	vel = velocidad;
	boss = EnemyManager::getInstance()->getActiveBoss();
	if(dir == 5)
	posInic = boss->getCenterPos().getX()-wheel->getCenterPos().getX();
	else 	posInic = wheel->getCenterPos().getX()- boss->getCenterPos().getX() ;
}


UpdateWheel::~UpdateWheel()
{
}
void UpdateWheel::receiveMessage(Message * msg)
{
	switch (msg->id) {
	case HURT:
		break;
	case MC_ATTACK_DAMAGE:
		break;
	}
}
void UpdateWheel::changeColor(int r, int g, int b)
{
	wheel->getCurrentAnimation()->changeColor(r, g, b);
}


void UpdateWheel::update()
{
	wheel->allUpdates();
	updateado = false;
	if (faseAct == 1 && (tiempo->TimeSinceTimerCreation < tiempoFase1) && !updateado)
	{
		fase1();
	}
	if (faseAct == 1 && !updateado && wheel->getCurrentAnimation()->isFinished())
	{
		tiempo->restart();
		faseAct = 2;
		updateado = true;
	}
	if (faseAct == 2 && tiempo->TimeSinceTimerCreation < tiempoFase2 && !updateado)
	{
		fase2();
	}
	else if (faseAct == 2 && !updateado)
	{
		tiempo->restart();
		faseAct = 3;
		updateado = true;
	}
	if (faseAct == 3 && tiempo->TimeSinceTimerCreation < tiempoFase3 && !updateado)
	{
		fase3();
	}
	if (faseAct == 3 && !updateado && wheel->getCurrentAnimation()->isFinished())
	{
		tiempo->restart();
		faseAct = 0;
		updateado = true;
		wheel->setInvisible(false);
		setActive(false);
	}

	tiempo->update();
}



void UpdateWheel::fase1()
{
	if (tiempo->TimeSinceTimerCreation == 0)
	{
		wheel->changeCurrentAnimation("SALE");
		wheel->getCurrentAnimation()->startAnimation();
		wheel->setInvisible(true);
	}
}

void UpdateWheel::fase2()
{
	if (tiempo->TimeSinceTimerCreation == 0)
	{
		wheel->changeCurrentAnimation("GIRA");
		wheel->getCurrentAnimation()->startAnimation();
	}

	if (dir == 4)
	{
		posProta = prota->getCenterPos();
		direccion = posProta - wheel->getCenterPos();
		direccion.normalize();
	}
	else if (dir == 0) direccion = Vector2D(1, 0);
	else if (dir == 1) direccion = Vector2D(0, 1);
	else if (dir == 2) direccion = Vector2D(-1, 0);
	else if (dir == 3) direccion = Vector2D(0, -1);
	else if (dir == 5) direccion = Vector2D(0, 1);
	else if (dir == 6) direccion = Vector2D(1, 0);
	else if (dir == 7) direccion = Vector2D(0, -1);
	else if (dir == 8) direccion = Vector2D(-1, 0);

	float auxVel = vel;
	if (dir == 5 && (wheel->getCenterPos().getY() >= boss->getCenterPos().getY() + posInic-60))
	{
		dir = 6;
		//auxVel = abs(wheel->getCenterPos().getX() - boss->getCenterPos().getX()) * 2/((1/vel)*100);
	}
	if (dir == 6 && (wheel->getCenterPos().getX() >= boss->getCenterPos().getX() + posInic-10))
	{
		dir = 7;
		//auxVel = abs(wheel->getCenterPos().getY() - boss->getCenterPos().getY()) * 2 / ((1 / vel) * 100);
	}
	if (dir == 7 && (wheel->getCenterPos().getY() <= boss->getCenterPos().getY() - posInic))
	{
		dir = 8;
		//auxVel = abs(wheel->getCenterPos().getX() - boss->getCenterPos().getX()) * 2 / ((1 / vel) * 100);
	}
	if (dir == 8 && (wheel->getCenterPos().getX() <= boss->getCenterPos().getX() - posInic))
	{
		dir = 5;
		//auxVel = abs(wheel->getCenterPos().getY() - boss->getCenterPos().getY()) * 2 / ((1 / vel) * 100);
	}

	wheel->getTransform()->position = wheel->getTransform()->position + direccion*vel* Time::getInstance()->DeltaTime*45;
}
void UpdateWheel::fase3()
{
	if (tiempo->TimeSinceTimerCreation == 0)
	{
		wheel->changeCurrentAnimation("ENTRA");
		wheel->getCurrentAnimation()->setTime(0.1);
		wheel->getCurrentAnimation()->startAnimation();
	}
}
