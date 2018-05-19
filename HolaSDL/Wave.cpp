#include "Wave.h"
#include "Game.h"
#include "Camera.h"
#include "MainCharacter.h"
#include "Timer.h"
#include "Time.h"
#include "Vector2D.h"
#include "ResourceManager.h"
#include "BoxRenderer.h"

using namespace std;
Wave::Wave(Transform t) : Enemy(prota)
{
	transform.position.setX(t.position.getX());
	transform.position.setY(t.position.getY());
	posInic = Vector2D(transform.position.getX(), transform.position.getY());
}

Wave::Wave(MainCharacter* prot, int x, int y, int w, int h) : Enemy(prot)
{
	prota = prot;
	transform.position.setX(x);
	transform.position.setY(y);
	transform.body.w = w;
	transform.body.h = h;
	Attributes.meleeDmg = 20;
	allUpdates();
	loadAnimations();


	rend = new WaveAnimationComponent(this, animations);
	addComponent(rend);
}


Wave::~Wave()
{
}



void Wave::loadAnimations()
{
	Tileset* tileset = ResourceManager::getInstance()->getEnemyTileset(7);
	string animationPath = "../Animations/Enemies/Wave.tmx";


	//Animaciones
	Animation* carga = AnimationParser::parseAnimation(tileset, animationPath, "Carga", this, 0, 0, false, 0.075);
	Animation* explosion = AnimationParser::parseAnimation(tileset, animationPath, "Explosion", this, 0, 0, false, 0.05);
	

	//Nombres de animaciones
	animations.emplace("CARGA", carga);
	animations.emplace("EXPLOSION", explosion);
	
}


void Wave::setInvisible(bool inv)
{
	if (inv == true && !hasComponent(rend)) 
		addComponent(rend);
	else if(inv == false && hasComponent(rend))
		removeComponent(rend);
}