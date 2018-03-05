#include "Boss.h"
#include "Game.h"
#include "Camera.h"
#include "MainCharacter.h"

Boss::Boss(Game* game, Transform t) : GameObject(game)
{
	transform.position.setX(t.position.getX());
	transform.position.setY(t.position.getY());
}

Boss::Boss(Game* game, MainCharacter* prot, int x, int y, int w, int h) : GameObject(game)
{
	transform.position.setX(x);
	transform.position.setY(y);
	transform.body.w = w;
	transform.body.h = h;
	prota = prot;
	
}
Boss::~Boss()
{
}

void Boss::fase1()
{
	if (transform.position.getX() > prota->getTransform()->position.getX()+1)
	{
		transform.position.setX(transform.position.getX()-velocidad);
	}
	else if (transform.position.getX() < prota->getTransform()->position.getX()-1)
	{
		transform.position.setX(transform.position.getX() + velocidad);
	}
	if (transform.position.getY() > prota->getTransform()->position.getY() + 1)
	{
		transform.position.setY(transform.position.getY() - velocidad);
	}
	else if (transform.position.getY() < prota->getTransform()->position.getY() - 1)
	{
		transform.position.setY(transform.position.getY() + velocidad);
	}
}

void Boss::update()
{
	render();
	fase1();
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
