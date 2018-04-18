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

	loadAnimations();
	this->changeCurrentAnimation("CANSADO");

	rend = new RenderBoss(this);
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
	this->changeCurrentAnimation("NORMAL_ATTACK");
	Vector2D direccion;
	direccion = transform.position - posInic;
	direccion.normalize();
	transform.position.set(transform.position - direccion*Time::getInstance()->DeltaTime*velocidad*1.2f);
}
void Boss::fase3()
{
	this->changeCurrentAnimation("START_ATTACK_JUMP");
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

void Boss::loadAnimations()
{
	Tileset* tileset = ResourceManager::getInstance()->getBoss1Tileset(0);
	string animationPath = "../Animations/Bosses/Boss1/Boss1.tmx";

	//Animaciones
	Animation* desvanece = AnimationParser::parseAnimation(tileset, animationPath, "Desvanece", this, 0, 0, false, 0.1);
	Animation* aparece = AnimationParser::parseAnimation(tileset, animationPath, "Aparece", this, 0, 0, false, 0.1);
	Animation* cansado = AnimationParser::parseAnimation(tileset, animationPath, "Cansado", this, 0, 0, true, 0.1);
	Animation* startJump = AnimationParser::parseAnimation(tileset, animationPath, "Boss1-StartJump", this, 0, 0, false, 0.1);
	Animation* startAttackJump = AnimationParser::parseAnimation(tileset, animationPath, "Boss1-StartAttackJump", this, 0, 0, false, 0.1);
	Animation* staticJump = AnimationParser::parseAnimation(tileset, animationPath, "Boss1-StaticJump", this, 0, 0, true, 0.1);
	Animation* normalFall = AnimationParser::parseAnimation(tileset, animationPath, "Boss1-NormalFall", this, 0, 0, false, 0.1);
	Animation* attackFall = AnimationParser::parseAnimation(tileset, animationPath, "Boss1-AttackFall", this, 0, 0, false, 0.1);
	Animation* estatico = AnimationParser::parseAnimation(tileset, animationPath, "Boss1-Static", this, 0, 0, true, 0.1);
	Animation* attack = AnimationParser::parseAnimation(tileset, animationPath, "Boss1-NormalAttack", this, 0, 0, false, 0.1);


	//Nombres de animaciones
	animations.emplace("DESVANECE", desvanece);
	animations.emplace("CANSADO", cansado);
	animations.emplace("APARECE", aparece);
	animations.emplace("START_JUMP", startJump);
	animations.emplace("START_ATTACK_JUMP", startAttackJump);
	animations.emplace("STATIC_JUMP", staticJump);
	animations.emplace("NORMAL_FALL", normalFall);
	animations.emplace("ATTACK_FALL", attackFall);
	animations.emplace("STATIC", estatico);
	animations.emplace("NORMAL_ATTACK", attack);
}
void Boss::update()
{
	cout << transform.position;
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
	this->getCurrentAnimation()->runAnimation();
}
