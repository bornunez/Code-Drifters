#include "UpdateBoss3.h"
#include "Boss3.h"
#include "EnemyManager.h"


UpdateBoss3::UpdateBoss3(GameObject* o, MainCharacter* prot) : UpdateComponent(o)
{
	boss = o;
	Tiempo = new Timer();
	prota = prot;
	posInic = Vector2D(boss->getTransform()->position.getX(), boss->getTransform()->position.getY());
}


UpdateBoss3::~UpdateBoss3()
{
}
void UpdateBoss3::receiveMessage(Message * msg)
{
	switch (msg->id) {
	case HURT:
		break;
	case MC_ATTACK_DAMAGE:
		break;
	}
}
void UpdateBoss3::changeColor(int r, int g, int b)
{
	boss->getCurrentAnimation()->changeColor(r, g, b);
	auxTimeHit = 0;
	hit = true;
}

void UpdateBoss3::Hit()
{
	if (auxTimeHit >= timeHit)
	{
		hit = false;
		boss->getCurrentAnimation()->changeColor(255, 255, 255);
	}
	else auxTimeHit += Time::getInstance()->DeltaTime;
}

void UpdateBoss3::update()
{
	boss->allUpdates();
	updateado = false;
	static_cast<Boss3*>(boss)->updateEnemies();
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
		faseAct = 8;
		updateado = true;
	}
	if (faseAct == 8 && Tiempo->TimeSinceTimerCreation < tiempoFase8 && !updateado)
	{
		fase8();
	}
	else if (faseAct == 8 && !updateado)
	{
		Tiempo->restart();
		faseAct = 9;
		updateado = true;
	}
	if (faseAct == 9 && Tiempo->TimeSinceTimerCreation < tiempoFase9 && !updateado)
	{
		fase9();
	}
	else if (faseAct == 9 && !updateado)
	{
		Tiempo->restart();
		faseAct = 0;
		updateado = true;
	}

	if (hit) Hit();
	Tiempo->update();
}



void UpdateBoss3::fase0()
{
	if (Tiempo->TimeSinceTimerCreation == 0)
	{
		boss->changeCurrentAnimation("ABRE_BRAZOS");
		boss->getTransform()->overlapCollision.active = true;
		boss->getCurrentAnimation()->startAnimation();
		fasesPast = 1;
		//static_cast<Boss2*>(boss)->createWheel(boss->getTransform()->position.getX() + 300, boss->getTransform()->position.getY());
	}
}

void UpdateBoss3::fase1()
{
	if (Tiempo->TimeSinceTimerCreation == 0)
	{
		boss->changeCurrentAnimation("ABRE_BRAZOS");
		boss->getCurrentAnimation()->startAnimation();
		Transform auxTrans;
		auxTrans.body.w = auxTrans.body.h = 20;
		auxTrans.position.set(boss->getCenterPos());
		auxTrans.velocity = Vector2D(0, -1);
		auxTrans.direction = Vector2D(0, -1);
		auxTrans.speed = 400;
		auxShoot(auxTrans);
		fasesPast = 0;
	}
	else if (Tiempo->TimeSinceTimerCreation >= tiempoFase1/5 && fasesPast == 0)
	{
		fasesPast++;
		Transform auxTrans;
		auxTrans.body.w = auxTrans.body.h = 20;
		auxTrans.position.set(boss->getCenterPos());
		auxTrans.velocity = Vector2D(0, -1);
		auxTrans.direction = Vector2D(0, -1);
		auxTrans.speed = 400;
		auxTrans.direction.rotate(30);
		auxTrans.velocity.rotate(30);
		auxShoot(auxTrans);
	}
}

void UpdateBoss3::fase2()
{
	if (Tiempo->TimeSinceTimerCreation == 0)
	{
		//boss->changeCurrentAnimation("WARNING");
		//boss->getCurrentAnimation()->startAnimation();
	}
}
void UpdateBoss3::fase3()
{
	velocidad = 100;
	if (Tiempo->TimeSinceTimerCreation == 0)
	{
		boss->getTransform()->position = Vector2D(1650, 1000);
		//boss->changeCurrentAnimation("SACA_RAYOS");
		//boss->getCurrentAnimation()->setTime(0.1);
		//boss->getCurrentAnimation()->startAnimation();
		auxLucian = 0;
	}
	if (auxInterval < tiempoIntervalLucian) 
	{
		auxInterval += Time::getInstance()->DeltaTime;
	}
	else if (auxLucian < tiempoLucian)
	{
		auxLucian += Time::getInstance()->DeltaTime;
		Transform auxTrans;
		auxTrans.body.w = auxTrans.body.h = 20;

		auxTrans.velocity = Vector2D(-1, 0);
		auxTrans.direction = Vector2D(-1, 0);
		auxTrans.speed = 400;
		if (arriba)
		{
			arriba = false;
			auxTrans.position.set(boss->getCenterPos() + Vector2D(0, 10));
		}
		else
		{
			arriba = true;
			auxTrans.position.set(boss->getCenterPos() - Vector2D(0, 10));
		}
		BulletManager::getInstance()->shoot(boss, auxTrans, BulletType::GunnerBullet);
		auxInterval = 0;
	}

	if (prota->getTransform()->position.getY() > boss->getTransform()->position.getY())
	{
		boss->getTransform()->position.setY(boss->getTransform()->position.getY()+Time::getInstance()->DeltaTime*velocidad);
	}
	else if (prota->getTransform()->position.getY() < boss->getTransform()->position.getY())
	{
		boss->getTransform()->position.setY(boss->getTransform()->position.getY()-Time::getInstance()->DeltaTime*velocidad);
	}
}

void UpdateBoss3::fase4()
{
	if (Tiempo->TimeSinceTimerCreation == 0)
	{
		//boss->changeCurrentAnimation("GIRA");
		//boss->getCurrentAnimation()->startAnimation();
		auxX = 600;
		boss->getTransform()->position = Vector2D(posInic.getX()+auxX, 500);
	}
	if (boss->getTransform()->position.getX() < (posInic.getX()-auxX)) dir = 1;
	else if (boss->getTransform()->position.getX() > (posInic.getX() + auxX)) dir = -1;
	boss->getTransform()->position.setY(boss->getTransform()->position.getY()+Time::getInstance()->DeltaTime*velocidad/2);
	boss->getTransform()->position.setX(boss->getTransform()->position.getX() + Time::getInstance()->DeltaTime*velocidad*10*dir);

	if (auxBomb < tiempoBomb)
	{
		auxBomb += Time::getInstance()->DeltaTime;
	}
	else
	{
		EnemyManager::getInstance()->spawn(boss->getCenterPos().getX(), boss->getCenterPos().getY(), Bomb);
		auxBomb = 0;
	}


	//boss->getCurrentAnimation()->setTime(auxVelocidad);
}
void UpdateBoss3::fase5()
{
	if (Tiempo->TimeSinceTimerCreation == 0)
	{
		//boss->changeCurrentAnimation("SACA_RAYOS");
		//boss->getCurrentAnimation()->setTime(-0.1);
		//boss->getCurrentAnimation()->startAnimation();

	}
}
void UpdateBoss3::fase6()
{
	if (Tiempo->TimeSinceTimerCreation == 0)
	{
		//boss->changeCurrentAnimation("WARNING");
		//boss->getCurrentAnimation()->startAnimation();
	}
}
void UpdateBoss3::fase7()
{
	if (Tiempo->TimeSinceTimerCreation == 0)
	{
		//boss->changeCurrentAnimation("ENTRA");
		//boss->getTransform()->overlapCollision.active = false;
		//boss->getCurrentAnimation()->startAnimation();
	}
}

void UpdateBoss3::fase8()
{
	if (Tiempo->TimeSinceTimerCreation == 0)
	{
		//boss->changeCurrentAnimation("ENTRA");
		//boss->getCurrentAnimation()->startAnimation();
		fasesPast = 1;
		boss->getTransform()->overlapCollision.active = false;

		static_cast<Boss3*>(boss)->createWheel(boss->getTransform()->position.getX() + 300, boss->getTransform()->position.getY(), velWheel, 4);
	}
}
void UpdateBoss3::fase9()
{
	if (Tiempo->TimeSinceTimerCreation == 0)
	{
		//boss->changeCurrentAnimation("SALE");
		//boss->getCurrentAnimation()->startAnimation();
		//boss->getTransform()->overlapCollision.active = true;
		fasesPast = 1;
		RondaWheels2();
		//static_cast<Boss2*>(boss)->createWheel(boss->getTransform()->position.getX() + 300, boss->getTransform()->position.getY());
	}
}
void UpdateBoss3::RondaWheels()
{
	dirWheel = Random::randomInt(0, 3);
	if (dirWheel == 0)
	{
		int salto = Random::randomInt(0, 7);
		if (salto != 0)static_cast<Boss3*>(boss)->createWheel(625, 550, velWheel, dirWheel);
		if (salto != 1)static_cast<Boss3*>(boss)->createWheel(625, 675, velWheel, dirWheel);
		if (salto != 2)static_cast<Boss3*>(boss)->createWheel(625, 800, velWheel, dirWheel);
		if (salto != 3)static_cast<Boss3*>(boss)->createWheel(625, 925, velWheel, dirWheel);
		if (salto != 4)static_cast<Boss3*>(boss)->createWheel(625, 1050, velWheel, dirWheel);
		if (salto != 5)static_cast<Boss3*>(boss)->createWheel(625, 1175, velWheel, dirWheel);
		if (salto != 6)static_cast<Boss3*>(boss)->createWheel(625, 1300, velWheel, dirWheel);
		if (salto != 7)static_cast<Boss3*>(boss)->createWheel(625, 1425, velWheel, dirWheel);
	}
	else if (dirWheel == 1)
	{
		int salto = Random::randomInt(0, 7);
		if (salto != 0)static_cast<Boss3*>(boss)->createWheel(625, 550, velWheel, dirWheel);
		if (salto != 1)static_cast<Boss3*>(boss)->createWheel(775, 550, velWheel, dirWheel);
		if (salto != 2)static_cast<Boss3*>(boss)->createWheel(925, 550, velWheel, dirWheel);
		if (salto != 3)static_cast<Boss3*>(boss)->createWheel(1075, 550, velWheel, dirWheel);
		if (salto != 4)static_cast<Boss3*>(boss)->createWheel(1225, 550, velWheel, dirWheel);
		if (salto != 5)static_cast<Boss3*>(boss)->createWheel(1375, 550, velWheel, dirWheel);
		if (salto != 6)static_cast<Boss3*>(boss)->createWheel(1525, 550, velWheel, dirWheel);
		if (salto != 7)static_cast<Boss3*>(boss)->createWheel(1675, 550, velWheel, dirWheel);
	}
	else if (dirWheel == 2)
	{
		int salto = Random::randomInt(0, 7);
		if (salto != 0)static_cast<Boss3*>(boss)->createWheel(1675, 550, velWheel, dirWheel);
		if (salto != 1)static_cast<Boss3*>(boss)->createWheel(1675, 675, velWheel, dirWheel);
		if (salto != 2)static_cast<Boss3*>(boss)->createWheel(1675, 800, velWheel, dirWheel);
		if (salto != 3)static_cast<Boss3*>(boss)->createWheel(1675, 925, velWheel, dirWheel);
		if (salto != 4)static_cast<Boss3*>(boss)->createWheel(1675, 1050, velWheel, dirWheel);
		if (salto != 5)static_cast<Boss3*>(boss)->createWheel(1675, 1175, velWheel, dirWheel);
		if (salto != 6)static_cast<Boss3*>(boss)->createWheel(1675, 1300, velWheel, dirWheel);
		if (salto != 7)static_cast<Boss3*>(boss)->createWheel(1675, 1425, velWheel, dirWheel);
	}
	else if (dirWheel == 3)
	{
		int salto = Random::randomInt(0, 7);
		if (salto != 0)static_cast<Boss3*>(boss)->createWheel(625, 1425, velWheel, dirWheel);
		if (salto != 1)static_cast<Boss3*>(boss)->createWheel(775, 1425, velWheel, dirWheel);
		if (salto != 2)static_cast<Boss3*>(boss)->createWheel(925, 1425, velWheel, dirWheel);
		if (salto != 3)static_cast<Boss3*>(boss)->createWheel(1075, 1425, velWheel, dirWheel);
		if (salto != 4)static_cast<Boss3*>(boss)->createWheel(1225, 1425, velWheel, dirWheel);
		if (salto != 5)static_cast<Boss3*>(boss)->createWheel(1375, 1425, velWheel, dirWheel);
		if (salto != 6)static_cast<Boss3*>(boss)->createWheel(1525, 1425, velWheel, dirWheel);
		if (salto != 7)static_cast<Boss3*>(boss)->createWheel(1675, 1425, velWheel, dirWheel);
	}
}

void UpdateBoss3::RondaWheels2()
{
	Vector2D pos = boss->getCenterPos();
	//Izquierda
	static_cast<Boss3*>(boss)->createWheel(pos.getX() - 180, pos.getY() - 50, velWheel, 5);
	static_cast<Boss3*>(boss)->createWheel(pos.getX() - 280, pos.getY() - 50, velWheel*1.5, 5);
	static_cast<Boss3*>(boss)->createWheel(pos.getX() - 380, pos.getY() - 50, velWheel * 2, 5);
	static_cast<Boss3*>(boss)->createWheel(pos.getX() - 480, pos.getY() - 50, velWheel*2.5, 5);

	//Derecha
	static_cast<Boss3*>(boss)->createWheel(pos.getX() + 112, pos.getY() - 50, velWheel, 7);
	static_cast<Boss3*>(boss)->createWheel(pos.getX() + 212, pos.getY() - 50, velWheel*1.5, 7);
	static_cast<Boss3*>(boss)->createWheel(pos.getX() + 312, pos.getY() - 50, velWheel * 2, 7);
	static_cast<Boss3*>(boss)->createWheel(pos.getX() + 412, pos.getY() - 50, velWheel*2.5, 7);
}

void UpdateBoss3::auxShoot(Transform auxTrans)
{
	BulletManager::getInstance()->shoot(boss, auxTrans, BulletType::GunnerBullet);
	auxTrans.direction.rotate(60);
	auxTrans.velocity.rotate(60);
	BulletManager::getInstance()->shoot(boss, auxTrans, BulletType::GunnerBullet);
	auxTrans.direction.rotate(60);
	auxTrans.velocity.rotate(60);
	BulletManager::getInstance()->shoot(boss, auxTrans, BulletType::GunnerBullet);
	auxTrans.direction.rotate(60);
	auxTrans.velocity.rotate(60);
	BulletManager::getInstance()->shoot(boss, auxTrans, BulletType::GunnerBullet);
	auxTrans.direction.rotate(60);
	auxTrans.velocity.rotate(60);
	BulletManager::getInstance()->shoot(boss, auxTrans, BulletType::GunnerBullet);
	auxTrans.direction.rotate(60);
	auxTrans.velocity.rotate(60);
	BulletManager::getInstance()->shoot(boss, auxTrans, BulletType::GunnerBullet);
}
