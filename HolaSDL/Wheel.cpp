#include "Wheel.h"
#include "Game.h"
#include "Camera.h"
#include "MainCharacter.h"
#include "Timer.h"
#include "Time.h"
#include "Vector2D.h"
#include "ResourceManager.h"
#include "BoxRenderer.h"

using namespace std;
Wheel::Wheel(Transform t) : Enemy(prota)
{
	transform.position.setX(t.position.getX());
	transform.position.setY(t.position.getY());
	posInic = Vector2D(transform.position.getX(), transform.position.getY());
}

Wheel::Wheel(MainCharacter* prot, int x, int y, int w, int h, float velocidad, int dir) : Enemy(prot)
{
	prota = prot;
	transform.position.setX(x);
	transform.position.setY(y);
	transform.body.w = w;
	transform.body.h = h;
	Attributes.meleeDmg = 10;
	allUpdates();
	loadAnimations();
	this->changeCurrentAnimation("SALE");
	this->getCurrentAnimation()->startAnimation();

	updat = new UpdateWheel(this, prota, velocidad, dir);
	addComponent(updat);
	rend = new RenderWheel(this);
	addComponent(rend);


	//BoxRenderer* skel = new BoxRenderer(this, playState->getCamera());
	//addComponent(skel);
}
Wheel::~Wheel()
{
}



void Wheel::loadAnimations()
{
	Tileset* tileset = ResourceManager::getInstance()->getEnemyTileset(4);
	string animationPath = "../Animations/Enemies/Wheel.tmx";


	//Animaciones
	Animation* sale = AnimationParser::parseAnimation(tileset, animationPath, "Wheel-Sale", this, 0, 0, false, 0.075);
	Animation* gira = AnimationParser::parseAnimation(tileset, animationPath, "Wheel-Gira", this, 0, 0, true, 0.05);
	Animation* entra = AnimationParser::parseAnimation(tileset, animationPath, "Wheel-Entra", this, 0, 0, false, 0.075);
	

	//Nombres de animaciones
	animations.emplace("SALE", sale);
	animations.emplace("GIRA", gira);
	animations.emplace("ENTRA", entra);
	
}


void Wheel::death()
{
	map<const char*, Animation*>::iterator it;
	for (it = animations.begin(); it != animations.end(); it++)
	{
		it->second->changeColor(0, 0, 0);
	}
}

void Wheel::changeColor(int r, int g, int b)
{
	updat->changeColor(255, 100, 100);
}

void Wheel::setInvisible(bool inv)
{
	if (inv == true && !hasComponent(rend)) 
		addComponent(rend);
	else if(inv == false && hasComponent(rend))
		removeComponent(rend);
}