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
Boss2::Boss2(Transform t) : MasterBoss()
{
	transform.position.setX(t.position.getX());
	transform.position.setY(t.position.getY());
	posInic = Vector2D(transform.position.getX(), transform.position.getY());
}

Boss2::Boss2(MainCharacter* prot, int x, int y, int w, int h) : MasterBoss()
{

	transform.position.setX(x);
	transform.position.setY(y);
	transform.body.w = w;
	transform.body.h = h;
	prota = prot;
	posInic = Vector2D(transform.position.getX(), transform.position.getY());
	Attributes.life = 500;
	Attributes.meleeDmg = 10;
	allUpdates();
	loadAnimations();
	this->changeCurrentAnimation("STATIC_UP");

	updat = new UpdateBoss2(this, prota);
	addComponent(updat);
	rend = new RenderBoss2(this);
	addComponent(rend);
	//addComponent(new DamageableBossComponent(this, prota));


	BoxRenderer* skel = new BoxRenderer(this, playState->getCamera());
	addComponent(skel);
}
Boss2::~Boss2()
{
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
	/*Animation* normalFall = AnimationParser::parseAnimation(tileset, animationPath, "Boss1-NormalFall", this, 0, -75, false, 0.1);
	Animation* attackFall = AnimationParser::parseAnimation(tileset, animationPath, "Boss1-AttackFall", this, 0, -75, false, 0.1);
	Animation* estatico = AnimationParser::parseAnimation(tileset, animationPath, "Boss1-Static", this, 0, -75, true, 0.1);
	Animation* attack = AnimationParser::parseAnimation(tileset, animationPath, "Boss1-NormalAttack", this, 0, 0, false, 0.1);
	*/

	//Nombres de animaciones
	animations.emplace("SALE", sale);
	animations.emplace("GIRA", gira);
	animations.emplace("WARNING", warning);
	animations.emplace("SACA_RAYOS", sacaRayos);
	animations.emplace("ENTRA", entra);
	animations.emplace("STATIC_DOWN", staticDown);
	/*animations.emplace("NORMAL_FALL", normalFall);
	animations.emplace("ATTACK_FALL", attackFall);
	animations.emplace("STATIC", estatico);
	animations.emplace("NORMAL_ATTACK", attack);
	*/
}

