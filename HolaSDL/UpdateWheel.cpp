#include "UpdateWheel.h"



UpdateWheel::UpdateWheel(GameObject* o, MainCharacter* prot) : UpdateComponent(o)
{
	wheel = o;
	prota = prot;
	tiempo = new Timer();
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
	else if (faseAct == 1 && !updateado)
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
	else if (faseAct == 3 && !updateado)
	{
		tiempo->restart();
		faseAct = 1;
		updateado = true;
	}

	tiempo->update();
}



void UpdateWheel::fase1()
{
	if (tiempo->TimeSinceTimerCreation == 0)
	{
		wheel->changeCurrentAnimation("SALE");
		wheel->getCurrentAnimation()->startAnimation();
	}
}

void UpdateWheel::fase2()
{
	if (tiempo->TimeSinceTimerCreation == 0)
	{
		wheel->changeCurrentAnimation("GIRA");
		wheel->getCurrentAnimation()->startAnimation();
	}

	posProta = prota->getCenterPos();
	direccion = posProta - wheel->getCenterPos();
	direccion.normalize();
	wheel->getTransform()->position = wheel->getTransform()->position + direccion;
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
