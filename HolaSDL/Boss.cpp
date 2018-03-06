#include "Boss.h"
#include "Game.h"
#include "Camera.h"
#include "MainCharacter.h"
#include "Timer.h"

Boss::Boss(Game* game, Transform t) : GameObject(game)
{
	Time = new Timer();
	transform.position.setX(t.position.getX());
	transform.position.setY(t.position.getY());
	posInic = Vector2D(transform.position.getX(), transform.position.getY());
	cout << posInic;
}

Boss::Boss(Game* game, MainCharacter* prot, int x, int y, int w, int h) : GameObject(game)
{
	Time = new Timer();
	transform.position.setX(x);
	transform.position.setY(y);
	transform.body.w = w;
	transform.body.h = h;
	prota = prot;
	posInic = Vector2D(transform.position.getX(), transform.position.getY());
	
}
Boss::~Boss()
{
}

void Boss::fase1()
{
	if (transform.position.getX() > prota->getTransform()->position.getX()+1)
	{
		transform.position.setX(transform.position.getX()-velocidad*(Time->DeltaTime+1));
	}
	else if (transform.position.getX() < prota->getTransform()->position.getX()-1)
	{
		transform.position.setX(transform.position.getX() + velocidad*(Time->DeltaTime + 1));
	}
	if (transform.position.getY() > prota->getTransform()->position.getY() + 1)
	{
		transform.position.setY(transform.position.getY() - velocidad*(Time->DeltaTime + 1));
	}
	else if (transform.position.getY() < prota->getTransform()->position.getY() - 1)
	{
		transform.position.setY(transform.position.getY() + velocidad*(Time->DeltaTime + 1));
	}
}

void Boss::fase2()
{
	//X
	float auxX = posInic.getX() - transform.position.getX();
	float recorridoX = 0;
	float auxVelX;
	if (auxX < 0) auxVelX = -velocidad;
	else auxVelX = velocidad;
	if ((auxX > 0 && recorridoX < auxX) || auxX < 0 && recorridoX>auxX)
		transform.position.setX(transform.position.getX()+auxVelX*(Time->DeltaTime+1));
	recorridoX += velocidad*(Time->DeltaTime+1);

	//Y
	float auxY = posInic.getY() - transform.position.getY();
	float recorridoY = 0;
	float auxVelY;
	if (auxY < 0) auxVelY = -velocidad;
	else auxVelY = velocidad;
	if ((auxY > 0 && recorridoY < auxY) || auxY < 0 && recorridoY>auxY)
		transform.position.setY(transform.position.getY() + auxVelY*(Time->DeltaTime + 1));
	recorridoY += velocidad*(Time->DeltaTime + 1);
}

void Boss::update()
{
	Time->update();
	render();
	if (Time->TimeSinceTimerCreation< tiempoFase1)
	{
		fase1();
		faseAct = 1;
	}
	else if (Time->TimeSinceTimerCreation < tiempoFase1+tiempoFase2)
	{
		fase2();
		faseAct = 2;
	}
}

void Boss::render()
{
	float auxX = transform.position.getX() - getGame()->getCamera()->getTransform()->position.getX();
	float auxY = transform.position.getY() - getGame()->getCamera()->getTransform()->position.getY();
	SDL_Rect rect RECT(auxX, auxY, transform.body.w, transform.body.h);
	SDL_SetRenderDrawColor(game->getRenderer(), COLOR(0xff000fff));
	SDL_RenderFillRect(game->getRenderer(), &rect);
	SDL_SetRenderDrawColor(game->getRenderer(), COLOR(0x000000ff));
}
