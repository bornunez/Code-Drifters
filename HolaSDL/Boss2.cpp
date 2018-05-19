#include "Boss2.h"
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
#include "BoxRenderer.h"
#include "DamageableBossComponent.h"

using namespace std;
Boss2::Boss2(Transform t) : MasterBoss(2)
{
	transform.position.setX(t.position.getX());
	transform.position.setY(t.position.getY());
	posInic = Vector2D(transform.position.getX(), transform.position.getY());
}

Boss2::Boss2(MainCharacter* prot, int x, int y, int w, int h) : MasterBoss(2)
{
	transform.position.setX(x);
	transform.position.setY(y);
	transform.body.w = w;
	transform.body.h = h;
	transform.body.w = w*1.6;
	transform.body.h = h/1.2;
	setSpriteOffset(1 * Game::getGame()->getScale(), -8 * Game::getGame()->getScale());

	transform.overlapCollision.overlapBody.w = w *1.6;
	transform.overlapCollision.overlapBody.h = h*1.1;
	transform.overlapCollision.overlapOffset.setX(1);
	transform.overlapCollision.overlapOffset.setY(-20);

	prota = prot;
	posInic = Vector2D(transform.position.getX(), transform.position.getY());
	Attributes.life = 3000;
	Attributes.maxHP = Attributes.life;
	Attributes.meleeDmg = 8;
	allUpdates();
	loadAnimations();
	this->changeCurrentAnimation("STATIC_DOWN");

	updat = new UpdateBoss2(this, prota);
	addComponent(updat);
	rend = new RenderBoss2(this);
	addComponent(rend);
	addComponent(new DamageableBossComponent(this, prota,0.2));

	ResourceManager::getInstance()->getMusic(Level1)->stop();
	ResourceManager::getInstance()->getMusic(Button)->play();
	//addComponent(new SkeletonRendered(this, playState->getCamera()));


	//BoxRenderer* skel = new BoxRenderer(this, playState->getCamera());
	//addComponent(skel);

}
Boss2::~Boss2()
{
	for (Wheel* obj : wheels)
		delete obj;

	wheels.clear();
}



void Boss2::loadAnimations()
{
	Tileset* tileset = ResourceManager::getInstance()->getBoss2Tileset(0);
	string animationPath = "../Animations/Bosses/Boss2/Boss2.tmx";

	//Animaciones
	Animation* sale = AnimationParser::parseAnimation(tileset, animationPath, "Boss2-Sale", this, 0, 0, false, 0.1);
	Animation* gira = AnimationParser::parseAnimation(tileset, animationPath, "Boss2-Gira", this, 0, 0, true, 0.8);
	Animation* warning = AnimationParser::parseAnimation(tileset, animationPath, "Boss2-Warning", this, 0, 0, true, 0.1);
	Animation* sacaRayos = AnimationParser::parseAnimation(tileset, animationPath, "Boss2-SacaRayos", this, 0, 0, false, 0.1);
	Animation* entra = AnimationParser::parseAnimation(tileset, animationPath, "Boss2-Entra", this, 0, 0, false, 0.1);
	Animation* staticDown = AnimationParser::parseAnimation(tileset, animationPath, "Boss2-StaticDown", this, 0, 0, true, 0.1);
	Animation* muere = AnimationParser::parseAnimation(tileset, animationPath, "Boss2-Muere", this, 0, 0, false, 0.1);

	//Nombres de animaciones
	animations.emplace("SALE", sale);
	animations.emplace("GIRA", gira);
	animations.emplace("WARNING", warning);
	animations.emplace("SACA_RAYOS", sacaRayos);
	animations.emplace("ENTRA", entra);
	animations.emplace("STATIC_DOWN", staticDown);
	animations.emplace("MUERE", muere);
}

void Boss2::changeColor(int r, int g, int b)
{
	updat->changeColor(255, 100, 100);
}

void Boss2::updateEnemies()
{
	for(int i = 0; i < wheels.size(); i++)
	{
		if (wheels[i] != nullptr)
		{
			wheels[i]->update();
		}
	}
}

void Boss2::renderEnemies()
{
	for (int i = 0; i < wheels.size(); i++)
	{
		if (wheels[i] != nullptr)
		{
			wheels[i]->render();
		}
	}
}
void Boss2::createWheel(int posX, int posY, float velocidad, int dir)
{
	int i = 0;
	bool pulled = false;
	while (i < wheels.size() && !pulled)
	{
		if (!wheels[i]->isActive())
		{
			wheels[i] = new Wheel(prota, posX, posY, 50, 50, velocidad, dir);
			pulled = true;
		}
		i++;
	}
	if (i == wheels.size())
	{
		wheels.push_back(new Wheel(prota, posX, posY, 50, 50, velocidad, dir));
	}
}

void Boss2::death()
{
	dead = true;
	ResourceManager::getInstance()->getSoundEffect(ButtonExplosion)->play();
	changeCurrentAnimation("MUERE");
	changeColor(255, 255, 255);
	for (int i = 0; i < wheels.size(); i++)
	{
		if (wheels[i] != nullptr)
		{
			wheels[i]->setActive(false);
			wheels[i]->changeCurrentAnimation("ENTRA");
			wheels[i]->getCurrentAnimation()->setTime(0.1);
			wheels[i]->getCurrentAnimation()->startAnimation();
		}
	}

}


