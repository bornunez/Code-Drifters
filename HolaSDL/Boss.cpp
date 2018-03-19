#include "Boss.h"
#include "Game.h"
#include "Camera.h"
#include "MainCharacter.h"
#include "Timer.h"
#include "Time.h"
#include "Vector2D.h"
#include "Bullet.h"
#include "ResourceManager.h"
#include "MCBulletComponent.h"
#include "MCBulletRenderComponent.h"

using namespace std;
Boss::Boss(Transform t) : MasterBoss()
{
	Time = new Timer();
	transform.position.setX(t.position.getX());
	transform.position.setY(t.position.getY());
	posInic = Vector2D(transform.position.getX(), transform.position.getY());
	cout << posInic;
}

Boss::Boss(MainCharacter* prot, int x, int y, int w, int h) : MasterBoss()
{

	Time = new Timer();
	transform.position.setX(x);
	transform.position.setY(y);
	transform.body.w = w;
	transform.body.h = h;
	prota = prot;
	posInic = Vector2D(transform.position.getX(), transform.position.getY());
	vida = 500;
	daño = 10;
	centro = new Vector2D(transform.body.w / 2, transform.body.h / 2);
	rend = new RenderBoss(this, centro);
	addComponent(rend);
	updat = new UpdateBoss(this);
	addComponent(updat);
}
Boss::~Boss()
{
}

void Boss::fase1()
{
	Vector2D direccion;
	posProta = prota->getTransform()->position + (Vector2D(prota->getTransform()->body.w / 2, prota->getTransform()->body.h/2));
	direccion = transform.position - posProta;
	direccion.normalize();
	transform.position.set(transform.position - direccion*Time::getInstance()->DeltaTime*velocidad);
}

void Boss::fase2()
{
	Vector2D direccion;
	direccion = transform.position - posInic;
	direccion.normalize();
	transform.position.set(transform.position - direccion*Time::getInstance()->DeltaTime*velocidad*1.2f);
}
void Boss::fase3()
{
	Vector2D direccion;
	Vector2D posExtrema;
	if (!saltado)
	{
		posProta = prota->getTransform()->position + (Vector2D(prota->getTransform()->body.w / 2, prota->getTransform()->body.h / 2));
		saltado = true;
	}
	if (Time->TimeSinceTimerCreation < tiempoFase3*0.8f)
	{
		direccion = transform.position - posProta;
		direccion.normalize();
		transform.position.set(transform.position - direccion*Time::getInstance()->DeltaTime*velocidad * 5);
	}
}

void Boss::fase4()
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
void Boss::update()
{
	Time->update();
	if (faseAct == 1 && Time->TimeSinceTimerCreation< tiempoFase1)
	{
		fase1();
		faseAct = 1;
	}
	else if(faseAct == 1)
	{
		Time->restart();
		faseAct = 2;
	}
	if (faseAct == 2 && Time->TimeSinceTimerCreation < tiempoFase2)
	{
		fase2();
		faseAct = 2;
	}
	else if(faseAct == 2)
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

void Boss::render()
{
	rend->render();
}
