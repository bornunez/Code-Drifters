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
void UpdateBoss::receiveMessage(Message * msg)
{
	switch (msg->id) {
	case HURT:
		break;
	}
}

void UpdateBoss::update()
{
	boss->allUpdates();
	updateado = false;
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
		faseAct = 1;
		if (fasesPast > 1)
		{
			faseAct = 3;
			fasesPast = 0;
		}
		else fasesPast++;
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
		faseAct = 1;
		updateado = true;
	}


	if (hit) Hit();
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
		boss->getTransform()->overlapCollision.active = false;
	}
	boss->getTransform()->position.set(boss->getTransform()->position-direccion*Time::getInstance()->DeltaTime*vel);
}

void UpdateBoss::fase2()
{
	if (Tiempo->TimeSinceTimerCreation == 0)
	{
		boss->changeCurrentAnimation("ATTACK_FALL");
		boss->getCurrentAnimation()->startAnimation();
		boss->getTransform()->overlapCollision.active = true;
	}
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
		boss->getTransform()->overlapCollision.active = false;
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
		boss->getTransform()->overlapCollision.active = true;
	}
	else if (boss->getCurrentAnimation()->isFinished() && boss->getCurrentAnimation()->getName() != "Boss1-NormalAttack")
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

void UpdateBoss::changeColor(int r, int g, int b)
{
	boss->getCurrentAnimation()->changeColor(r, g, b);
	auxTimeHit = 0;
	hit = true;
}

void UpdateBoss::Hit()
{

	if (auxTimeHit >= timeHit)
	{
		hit = false;
		boss->getCurrentAnimation()->changeColor(255, 255, 255);
	}
	else auxTimeHit += Time::getInstance()->DeltaTime;
}
