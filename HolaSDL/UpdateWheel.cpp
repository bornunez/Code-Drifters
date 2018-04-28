#include "UpdateWheel.h"
#include "Wheel.h"


UpdateWheel::UpdateWheel(GameObject* o, MainCharacter* prot, float velocidad, int direccion) : UpdateComponent(o)
{
	dir = direccion;
	wheel = o;
	prota = prot;
	tiempo = new Timer();
	vel = velocidad;
	posInic = Vector2D(wheel->getTransform()->position.getX(), wheel->getTransform()->position.getY());
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
		static_cast<Wheel*>(wheel)->setInvisible(false);
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
		static_cast<Wheel*>(wheel)->setInvisible(true);
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


	wheel->getTransform()->position = wheel->getTransform()->position + direccion*vel;
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
