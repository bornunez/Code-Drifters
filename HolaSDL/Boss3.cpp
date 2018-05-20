#include "Boss3.h"
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
Boss3::Boss3(Transform t) : MasterBoss(2)
{
	transform.position.setX(t.position.getX());
	transform.position.setY(t.position.getY());
	posInic = Vector2D(transform.position.getX(), transform.position.getY());
}

Boss3::Boss3(MainCharacter* prot, int x, int y, int w, int h) : MasterBoss(3)
{
	transform.position.setX(x);
	transform.position.setY(y);
	transform.body.w = w/1.5f;
	transform.body.h = h*1.1f;
	transform.body.w = w;
	transform.body.h = h;
	setSpriteOffset(1 * Game::getGame()->getScale(), -8 * Game::getGame()->getScale());

	transform.overlapCollision.overlapBody.w = w/1.25f;
	transform.overlapCollision.overlapBody.h = h;
	transform.overlapCollision.overlapOffset.setX(5);
	transform.overlapCollision.overlapOffset.setY(0);

	prota = prot;
	posInic = Vector2D(transform.position.getX(), transform.position.getY());
	Attributes.life = 6000;
	Attributes.maxHP = Attributes.life;
	Attributes.meleeDmg = 25;
	allUpdates();
	loadAnimations();
	this->changeCurrentAnimation("ABRE_BRAZOS");

	updat = new UpdateBoss3(this, prota);
	addComponent(updat);
	rend = new RenderBoss3(this);
	addComponent(rend);
	addComponent(new DamageableBossComponent(this, prota, 0.2));
	//addComponent(new SkeletonRendered(this, playState->getCamera()));

	ResourceManager::getInstance()->getMusic(Level2)->stop();
	ResourceManager::getInstance()->getMusic(FinalBoss1)->play();


	//BoxRenderer* skel = new BoxRenderer(this, playState->getCamera());
	//addComponent(skel);

}
Boss3::~Boss3()
{
}



void Boss3::loadAnimations()
{
	Tileset* tileset = ResourceManager::getInstance()->getBoss3Tileset(0);
	string animationPath = "../Animations/Bosses/Boss3/Boss3.tmx";

	//Animaciones
	Animation* abreBrazos = AnimationParser::parseAnimation(tileset, animationPath, "AbreBrazos", this, 0, 0, false, 0.04);
	Animation* carga = AnimationParser::parseAnimation(tileset, animationPath, "Carga", this, 0, 0, false, 0.1);
	Animation* swordashini = AnimationParser::parseAnimation(tileset, animationPath, "SwordDashIni", this, 0, 0, false, 0.1);
	Animation* swordDashLoop = AnimationParser::parseAnimation(tileset, animationPath, "SwordDashLoop", this, 0, 0, true, 0.1);
	Animation* swordDashEnd = AnimationParser::parseAnimation(tileset, animationPath, "SwordDashEnd", this, 0, 0, false, 0.1);
	Animation* aparece = AnimationParser::parseAnimation(tileset, animationPath, "Appear", this, 0, 0, false, 0.1);
	Animation* desaparece = AnimationParser::parseAnimation(tileset, animationPath, "Dissapear", this, 0, 0, false, 0.1);
	Animation* wall = AnimationParser::parseAnimation(tileset, animationPath, "WallShoot", this, 0, 0, true, 0.1);
	Animation* wave = AnimationParser::parseAnimation(tileset, animationPath, "Wave", this, 0, 0, false, 0.1);
	Animation* heal = AnimationParser::parseAnimation(tileset, animationPath, "Heal", this, 0, 0, true, 0.1);
	
	//Nombres de animaciones
	animations.emplace("ABRE_BRAZOS", abreBrazos);
	animations.emplace("CARGA", carga);
	animations.emplace("SWORD_DASH_INIT", swordashini);
	animations.emplace("SWORD_DASH_LOOP", swordDashLoop);
	animations.emplace("SWORD_DASH_END", swordDashEnd);
	animations.emplace("APARECE", aparece);
	animations.emplace("DESAPARECE", desaparece);
	animations.emplace("WALL_SHOOT", wall);
	animations.emplace("WAVE", wave);
	animations.emplace("HEAL", heal);
}

void Boss3::changeColor(int r, int g, int b)
{
	updat->changeColor(255, 100, 100);
	if (!epic && Attributes.life <= Attributes.maxHP / 2) {
		ResourceManager::getInstance()->getMusic(FinalBoss1)->stop();
		ResourceManager::getInstance()->getMusic(FinalBoss2)->play();
		epic = true;
	}
}
void Boss3::updateEnemies()
{
	for (int i = 0; i < waves.size(); i++)
	{
		if (waves[i] != nullptr)
		{
			waves[i]->update();
		}
	}
}

void Boss3::renderEnemies()
{
	for (int i = 0; i < waves.size(); i++)
	{
		if (waves[i] != nullptr)
		{
			waves[i]->render();
		}
	}
}
void Boss3::createWave(int posX, int posY)
{
	int i = 0;
	bool pulled = false;
	while (i < waves.size() && !pulled)
	{
		if (!waves[i]->isActive())
		{
			waves[i] = new Wave(prota, posX, posY, 50, 50);
			pulled = true;
		}
		i++;
	}
	if (i == waves.size())
	{
		waves.push_back(new Wave(prota, posX, posY, 50, 50));
	}
}

void Boss3::death()
{
	Game::getGame()->final();
}
