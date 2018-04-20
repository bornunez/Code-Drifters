#include "UpdateBoss.h"



UpdateBoss::UpdateBoss(GameObject* o, MainCharacter* prot) : UpdateComponent(o)
{
	boss = o;
	Time = new Timer();
	prota = prot;
}


UpdateBoss::~UpdateBoss()
{
}

void UpdateBoss::update()
{
	boss->updateBody();
	Time->update();
	if (faseAct == 1 && Time->TimeSinceTimerCreation< tiempoFase1)
	{
		fase1();
		faseAct = 1;
	}
	else if (faseAct == 1)
	{
		Time->restart();
		faseAct = 2;
	}
	if (faseAct == 2 && Time->TimeSinceTimerCreation < tiempoFase2)
	{
		fase2();
		faseAct = 2;
	}
	else if (faseAct == 2)
	{
		Time->restart();
		faseAct = 3;
		saltado = false;
	}
	if (faseAct == 3 && Time->TimeSinceTimerCreation < tiempoFase3)
	{
		fase3();
		faseAct = 3;
	}
	else if (faseAct == 3)
	{
		Time->restart();
		faseAct = 1;
	}
	if (faseAct == 4 && Time->TimeSinceTimerCreation < tiempoFase4)
	{
		fase4();
		faseAct = 4;
	}
	else if (faseAct == 4)
	{
		Time->restart();
		faseAct = 1;
	}
}

void UpdateBoss::fase1()
{
	Vector2D direccion;
	posProta = prota->getTransform()->position + (Vector2D(prota->getTransform()->body.w / 2, prota->getTransform()->body.h / 2));
	direccion = boss->getTransform()->position - posProta;
	direccion.normalize();
	boss->getTransform()->position.set(boss->getTransform()->position - direccion*Time::getInstance()->DeltaTime*velocidad);
}

void UpdateBoss::fase2()
{
	boss->changeCurrentAnimation("NORMAL_ATTACK");
	Vector2D direccion;
	direccion = boss->getTransform()->position - posInic;
	direccion.normalize();
	boss->getTransform()->position.set(boss->getTransform()->position - direccion*Time::getInstance()->DeltaTime*velocidad*1.2f);
}
void UpdateBoss::fase3()
{
	boss->changeCurrentAnimation("START_ATTACK_JUMP");
	Vector2D direccion;
	Vector2D posExtrema;
	if (!saltado)
	{
		posProta = prota->getTransform()->position + (Vector2D(prota->getTransform()->body.w / 2, prota->getTransform()->body.h / 2));
		saltado = true;
	}
	if (Time->TimeSinceTimerCreation < tiempoFase3*0.8f)
	{
		direccion = boss->getTransform()->position - posProta;
		direccion.normalize();
		boss->getTransform()->position.set(boss->getTransform()->position - direccion*Time::getInstance()->DeltaTime*velocidad * 5);
	}
}

void UpdateBoss::fase4()
{
	/*Transform bulletTransform;
	bulletTransform.position = transform.position;
	bulletTransform.body.w = bulletTransform.body.h = 50;
	bulletTransform.direction = prota->getTransform()->position - transform.position;//Resta la posición del cursor al del personaje
	bulletTransform.direction.normalize();
	Bullet* auxBullet = new Bullet(Game::getGame()->getResourceManager()->getTexture(BulletSprite), bulletTransform, true);
	auxBullet->addComponent(new MCBulletComponent(auxBullet, 1.5));
	auxBullet->addComponent(new MCBulletRenderComponent(auxBullet));
	*/
}
