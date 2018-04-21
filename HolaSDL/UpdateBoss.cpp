#include "UpdateBoss.h"



UpdateBoss::UpdateBoss(GameObject* o, MainCharacter* prot) : UpdateComponent(o)
{
	boss = o;
	Tiempo = new Timer();
	prota = prot;
	posInic = Vector2D(boss->getTransform()->position.getX(), boss->getTransform()->position.getY());
}


UpdateBoss::~UpdateBoss()
{
}

void UpdateBoss::update()
{
	boss->allUpdates();
	cout << faseAct;
	if (faseAct == 1 && (Tiempo->TimeSinceTimerCreation < tiempoFase1))
	{
		fase1();
	}
	else if (faseAct == 1)
	{
		Tiempo->restart();
		faseAct = 2;
	}
	if (faseAct == 2 && Tiempo->TimeSinceTimerCreation < tiempoFase2)
	{
		fase2();
	}
	else if (faseAct == 2)
	{
		Tiempo->restart();
		faseAct = 1;
		if (fasesPast > 1)
		{
			faseAct = 3;
			fasesPast = 0;
		}
		else fasesPast++;
	}
	if (faseAct == 3 && Tiempo->TimeSinceTimerCreation < tiempoFase3)
	{
		fase3();
	}
	else if (faseAct == 3)
	{
		Tiempo->restart();
		faseAct = 4;
	}
	if (faseAct == 4 && Tiempo->TimeSinceTimerCreation < tiempoFase4)
	{
		fase4();
	}
	else if (faseAct == 4)
	{
		Tiempo->restart();
		faseAct = 5;
	}
	if (faseAct == 5 && Tiempo->TimeSinceTimerCreation < tiempoFase5)
	{
		fase5();
	}
	else if (faseAct == 5)
	{
		Tiempo->restart();
		faseAct = 1;
	}
	Tiempo->update();
}

void UpdateBoss::fase1()
{
	if (Tiempo->TimeSinceTimerCreation == 0)
	{
		boss->changeCurrentAnimation("START_JUMP");
		boss->getCurrentAnimation()->startAnimation();
		posProta = prota->getCenterPos();
		direccion = boss->getCenterPos() - posProta;
		vel = direccion.magnitude() / tiempoFase1;
		direccion.normalize();
	}
	boss->getTransform()->position.set(boss->getTransform()->position-direccion*Time::getInstance()->DeltaTime*vel);
}

void UpdateBoss::fase2()
{
	if (Tiempo->TimeSinceTimerCreation == 0)
	{
		boss->changeCurrentAnimation("ATTACK_FALL");
		boss->getCurrentAnimation()->startAnimation();
	}
	//boss->getTransform()->position.set(boss->getTransform()->position - direccion*Time::getInstance()->DeltaTime*velocidad*1.2f);
}
void UpdateBoss::fase3()
{
	if (boss->getCurrentAnimation()->isFinished())
	{
		boss->changeCurrentAnimation("CANSADO");
		boss->getCurrentAnimation()->startAnimation();
	}
}

void UpdateBoss::fase4()
{
	if (Tiempo->TimeSinceTimerCreation == 0)
	{
		boss->changeCurrentAnimation("DESVANECE");
		boss->getCurrentAnimation()->startAnimation();
	}
}
void UpdateBoss::fase5()
{
	if (Tiempo->TimeSinceTimerCreation == 0)
	{
		direccion = prota->getCenterPos();
		boss->changeCurrentAnimation("APARECE");
		boss->getCurrentAnimation()->startAnimation();
		boss->getTransform()->position.set(direccion);
		boss->getTransform()->position.setX(boss->getTransform()->position.getX() - boss->getTransform()->body.w / 2);
		boss->getTransform()->position.setY(boss->getTransform()->position.getY() - boss->getTransform()->body.h / 2);
	}
	if (boss->getCurrentAnimation()->isFinished() && boss->getCurrentAnimation()->getName() != "Boss1-NormalAttack")
	{
		boss->changeCurrentAnimation("NORMAL_ATTACK");
		boss->getCurrentAnimation()->startAnimation();
		boss->getCurrentAnimation()->setFlip(SDL_FLIP_NONE);
	}
	else if (boss->getCurrentAnimation()->isFinished())
	{
		boss->getCurrentAnimation()->startAnimation();
		boss->getCurrentAnimation()->setFlip(SDL_FLIP_HORIZONTAL);
	}
}
