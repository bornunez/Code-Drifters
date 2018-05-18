#pragma once
//#include "checkML.h"
#include "MainCharacter.h"
#include "Game.h"
#include "Camera.h"
#include "PlayState.h"
#include "BasicMovement.h"
#include "MCShotComponent.h"
#include "MCAttackComponent.h"
#include "SkeletonRenderer.h"
#include "Texture.h"
#include "MCAnimationComponent.h"
#include "ResourceManager.h"
#include "MCMovementInput.h"
#include "AnimationParser.h"
#include "BoxRenderer.h"
#include "LevelExplorer.h"
#include "DoorsCollision.h"
#include "MCHookInputComponent.h"
#include "HookShotComponent.h"
#include "ExampleRender.h"
#include "HookAnimationComponent.h"
#include "ReloadComponent.h"
#include "MCGunPosition.h"
#include "MCManagerComponent.h"
#include "HUDManager.h"
#include "KnockbackComponent.h"
#include "MCChargedAttackComponent.h"
#include "MCUltimateInput.h"
#include "MCUltimateCharge.h"

//Personaje principal
MainCharacter::MainCharacter(Texture * tex, int x, int y, int w, int h)
	: GameObject(tex, x, y, w, h), HP(100), maxHP(100)
{
	transform.position.setX(x);
	transform.position.setY(y);
	transform.body.x = x; transform.body.y = y + h - (h/2.5);
	transform.body.w = w/2;
	transform.body.h = h/2.5;
	setSpriteOffset(0, -10 * Game::getGame()->getScale());

	transform.overlapCollision.overlapBody.w = w / 3;
	transform.overlapCollision.overlapBody.h = h / 1.5;
	transform.overlapCollision.overlapOffset.setX(2);
	transform.overlapCollision.overlapOffset.setY(-12);

	loadAnimations();

	hook = new Hook(500);
	PlayState::getInstance()->addGameObject(hook);
	transform.speed = 400;
	//setMaxVelocity(0.5);

	addComponent(new MCManagerComponent(this));
	setCollisionsLayers({ "Paredes","Aire" });
	addComponent(new MCGunPosition(this));
	addComponent(new ReloadComponent(this));
	addComponent(new MCShotComponent(this));
	addComponent(new MCAttackComponent(this));
	addComponent(new LevelExplorer(this));
	hookShot = new HookShotComponent(this,hook, 1000.0f);
	addComponent(hookShot);
	addComponent(new MCHookInputComponent(this));
	addComponent(new HookAnimationComponent(hook, ResourceManager::getInstance()->getTexture(HookChain), ResourceManager::getInstance()->getTexture(HookChainFail),ResourceManager::getInstance()->getTexture(HookHead)));
	addComponent(new MCMovementInput(this, SDL_SCANCODE_W, SDL_SCANCODE_D, SDL_SCANCODE_S, SDL_SCANCODE_A));
	addComponent(new MCAnimationComponent(this, animations));
	addComponent(new DoorsCollision(this));
	addComponent(new KnockbackComponent(this,1500));
	//addComponent(new SkeletonRendered(this, playState->getCamera()));	
	addComponent(new MCChargedAttackComponent(this, 0.4));
	addComponent(new MCUltimateInput(this));
	addComponent(new MCUltimateCharge(this));
	addComponent(new BasicMovement(this));
	//addComponent(new BoxRenderer(this, playState->getCamera()));

	maxBullets = 3;
	reloadTime = 5;
	currentBullets = maxBullets;

	normalAttackDamage = 50;
	chargedAttackDamage = 100;
	ultimateAttackDamage = 100;
	movable = true;
	
}

MainCharacter::~MainCharacter()
{
	/*delete hook;
	hook = nullptr;*/
}

void MainCharacter::loadAnimations()
{
	Tileset* tileset = ResourceManager::getInstance()->getProtaTileset(0);
	string animationPath = "../Animations/Protagonist/tileset/ProtaAnimation.tmx";
	int offsetY = 0;
	Animation* idleBot = AnimationParser::parseAnimation(tileset, animationPath, "IdleBot", this, 0, offsetY);
	Animation* idleTop = AnimationParser::parseAnimation(tileset, animationPath, "IdleTop", this, 0, offsetY);
	Animation* idleRight = AnimationParser::parseAnimation(tileset, animationPath, "IdleRight", this, 0, offsetY);
	Animation* idleLeft = AnimationParser::parseAnimation(tileset, animationPath, "IdleLeft", this, 0, offsetY);

	animations.emplace("IDLE_BOT", idleBot);
	animations.emplace("IDLE_TOP", idleTop);
	animations.emplace("IDLE_RIGHT", idleRight);
	animations.emplace("IDLE_LEFT", idleLeft);

	Animation*runBot = AnimationParser::parseAnimation(tileset, animationPath, "RunBot", this, 0, offsetY, true, 0.1);
	Animation*runTop = AnimationParser::parseAnimation(tileset, animationPath, "RunTop", this, 0, offsetY, true, 0.1);
	Animation*runRight = AnimationParser::parseAnimation(tileset, animationPath, "RunRight", this, 0, offsetY, true, 0.1);
	Animation*runLeft = AnimationParser::parseAnimation(tileset, animationPath, "RunLeft", this, 0, offsetY, true, 0.1);

	animations.emplace("RUN_BOT", runBot);
	animations.emplace("RUN_TOP", runTop);
	animations.emplace("RUN_RIGHT", runRight);
	animations.emplace("RUN_LEFT", runLeft);

	Animation*attackRight1 = AnimationParser::parseAnimation(tileset, animationPath, "AttackRight1", this, 10*Game::getGame()->getScale(), offsetY,false);
	Animation*attackRight2 = AnimationParser::parseAnimation(tileset, animationPath, "AttackRight2", this, 10 * Game::getGame()->getScale(), offsetY, false);
	Animation*attackRight3 = AnimationParser::parseAnimation(tileset, animationPath, "AttackRight3", this, 10 * Game::getGame()->getScale(), offsetY, false);

	animations.emplace("ATTACK1_RIGHT", attackRight1);
	animations.emplace("ATTACK2_RIGHT", attackRight2);
	animations.emplace("ATTACK3_RIGHT", attackRight3);

	Animation*attackLeft1 = AnimationParser::parseAnimation(tileset, animationPath, "AttackLeft1", this, -10 * Game::getGame()->getScale(), offsetY, false);
	Animation*attackLeft2 = AnimationParser::parseAnimation(tileset, animationPath, "AttackLeft2", this, -10 * Game::getGame()->getScale(), offsetY, false);
	Animation*attackLeft3 = AnimationParser::parseAnimation(tileset, animationPath, "AttackLeft3", this, -10 * Game::getGame()->getScale(), offsetY, false);

	animations.emplace("ATTACK1_LEFT", attackLeft1);
	animations.emplace("ATTACK2_LEFT", attackLeft2);
	animations.emplace("ATTACK3_LEFT", attackLeft3);

	Animation*attackTopLeft1 = AnimationParser::parseAnimation(tileset, animationPath, "AttackTopLeft1", this,0, -10 * Game::getGame()->getScale() + offsetY, false);
	Animation*attackTopLeft2  = AnimationParser::parseAnimation(tileset, animationPath, "AttackTopLeft2", this, 0, -10 * Game::getGame()->getScale() + offsetY, false);
	Animation*attackTopLeft3 = AnimationParser::parseAnimation(tileset, animationPath, "AttackTopLeft3", this, 0, -10 * Game::getGame()->getScale() + offsetY, false);
	
	animations.emplace("ATTACK1_TOPLEFT", attackTopLeft1);
	animations.emplace("ATTACK2_TOPLEFT", attackTopLeft2);
	animations.emplace("ATTACK3_TOPLEFT", attackTopLeft3);

	Animation*attackTopRight1  = AnimationParser::parseAnimation(tileset, animationPath, "AttackTopRight1", this, 0, -10 * Game::getGame()->getScale() + offsetY, false);
	Animation*attackTopRight2 = AnimationParser::parseAnimation(tileset, animationPath, "AttackTopRight2", this, 0, -10 * Game::getGame()->getScale() + offsetY, false);
	Animation*attackTopRight3 = AnimationParser::parseAnimation(tileset, animationPath, "AttackTopRight3", this, 0, -10 * Game::getGame()->getScale() + offsetY, false);

	animations.emplace("ATTACK1_TOPRIGHT", attackTopRight1);
	animations.emplace("ATTACK2_TOPRIGHT", attackTopRight2);
	animations.emplace("ATTACK3_TOPRIGHT", attackTopRight3);

	Animation*attackBotRight1 = AnimationParser::parseAnimation(tileset, animationPath, "AttackBotRight1", this, 0, offsetY, false);
	Animation*attackBotRight2 = AnimationParser::parseAnimation(tileset, animationPath, "AttackBotRight2", this, 0, offsetY, false);
	Animation*attackBotRight3 = AnimationParser::parseAnimation(tileset, animationPath, "AttackBotRight3", this, 0, offsetY, false);

	animations.emplace("ATTACK1_BOTRIGHT", attackBotRight1);
	animations.emplace("ATTACK2_BOTRIGHT", attackBotRight2);
	animations.emplace("ATTACK3_BOTRIGHT", attackBotRight3);

	Animation*attackBotLeft1 = AnimationParser::parseAnimation(tileset, animationPath, "AttackBotLeft1", this, 0, offsetY,false);
	Animation*attackBotLeft2 = AnimationParser::parseAnimation(tileset, animationPath, "AttackBotLeft2", this, 0, offsetY, false);
	Animation*attackBotLeft3 = AnimationParser::parseAnimation(tileset, animationPath, "AttackBotLeft3", this, 0, offsetY, false);

	animations.emplace("ATTACK1_BOTLEFT", attackBotLeft1);
	animations.emplace("ATTACK2_BOTLEFT", attackBotLeft2);
	animations.emplace("ATTACK3_BOTLEFT", attackBotLeft3);

	Animation*dashRight = AnimationParser::parseAnimation(tileset, animationPath, "DashRight", this, 0, offsetY);
	Animation*dashEndRight = AnimationParser::parseAnimation(tileset, animationPath, "DashEndRight", this, 0, offsetY, false,0.1);
	
	Animation*dashLeft = AnimationParser::parseAnimation(tileset, animationPath, "DashLeft", this, 0, offsetY);
	Animation*dashEndLeft = AnimationParser::parseAnimation(tileset, animationPath, "DashEndLeft", this, 0, offsetY, false,0.1);

	Animation*dashTop = AnimationParser::parseAnimation(tileset, animationPath, "DashTop", this, 0, offsetY);
	Animation*dashEndTop = AnimationParser::parseAnimation(tileset, animationPath, "DashEndTop", this, 0, offsetY, false,0.1);

	Animation*dashBot = AnimationParser::parseAnimation(tileset, animationPath, "DashBot", this, 0, offsetY);
	Animation*dashEndBot = AnimationParser::parseAnimation(tileset, animationPath, "DashEndBot", this, 0, offsetY, false,0.1);

	animations.emplace("DASH_RIGHT", dashRight);
	animations.emplace("DASHEND_RIGHT", dashEndRight);
	animations.emplace("DASH_LEFT", dashLeft);
	animations.emplace("DASHEND_LEFT", dashEndLeft);
	animations.emplace("DASH_TOP", dashTop);
	animations.emplace("DASHEND_TOP", dashEndTop);
	animations.emplace("DASH_BOT", dashBot);
	animations.emplace("DASHEND_BOT", dashEndBot);

	Animation* hurt = AnimationParser::parseAnimation(tileset, animationPath, "Hurt", this, 0, offsetY);

	animations.emplace("HURT", hurt);

	Animation* death = AnimationParser::parseAnimation(tileset, animationPath, "Death", this, 0, offsetY, false);

	animations.emplace("DEATH", death);

	Animation*shotRight = AnimationParser::parseAnimation(tileset, animationPath, "ShotRight", this, 0, offsetY);

	Animation*shotLeft = AnimationParser::parseAnimation(tileset, animationPath, "ShotLeft", this, -5*Game::getGame()->getScale(), offsetY);

	Animation*shotTop = AnimationParser::parseAnimation(tileset, animationPath, "ShotTop", this, 0, offsetY);

	Animation*shotBot = AnimationParser::parseAnimation(tileset, animationPath, "ShotBot", this, 0, offsetY);

	animations.emplace("SHOT_TOP", shotTop);
	animations.emplace("SHOT_LEFT", shotLeft);
	animations.emplace("SHOT_RIGHT", shotRight);
	animations.emplace("SHOT_BOT", shotBot);

	Animation*attackChargingTop = AnimationParser::parseAnimation(tileset, animationPath, "AttackChargingTop", this, 0, offsetY, true);
	Animation*attackChargedTop = AnimationParser::parseAnimation(tileset, animationPath, "AttackChargedTop", this, 0, offsetY, false);

	Animation*attackChargingBot = AnimationParser::parseAnimation(tileset, animationPath, "AttackChargingBot", this, 0, offsetY, true);
	Animation*attackChargedBot = AnimationParser::parseAnimation(tileset, animationPath, "AttackChargedBot", this, 0, offsetY, false);

	Animation*attackChargingRight = AnimationParser::parseAnimation(tileset, animationPath, "AttackChargingRight", this, 0, offsetY, true);
	Animation*attackChargedRight = AnimationParser::parseAnimation(tileset, animationPath, "AttackChargedRight", this, 0, offsetY, false);

	animations.emplace("ATTACKCHARGING_TOP", attackChargingTop);
	animations.emplace("ATTACKCHARGED_TOP", attackChargedTop);

	animations.emplace("ATTACKCHARGING_BOT", attackChargingBot);
	animations.emplace("ATTACKCHARGED_BOT", attackChargedBot);

	animations.emplace("ATTACKCHARGING_RIGHT", attackChargingRight);
	animations.emplace("ATTACKCHARGED_RIGHT", attackChargedRight);

	//Aquí se carga el Ultimate
	tileset = ResourceManager::getInstance()->getProtaTileset(1);
	animationPath = "../Animations/Protagonist/tileset/UltimateAnimation.tmx";

	Animation* ultimate = AnimationParser::parseAnimation(tileset, animationPath, "Ultimate", this, 0, offsetY - 50 * Game::getGame()->getScale(),false);

	animations.emplace("ULTIMATE", ultimate);

}

//Getters & Setters
float MainCharacter::getCurrentBullets()
{
	return currentBullets;
}
void MainCharacter::setCurrentBullets(float current)
{
	currentBullets = current;
}
void MainCharacter::setReloadTime(float newReloadTime)
{
	reloadTime = newReloadTime;
}
void MainCharacter::setMaxBullets(int bullets)
{
	maxBullets = bullets;
}
int MainCharacter::getMaxBullets()
{
	return maxBullets;
}
float MainCharacter::getNormalAttackDamage()
{
	return normalAttackDamage;
}
void MainCharacter::setNormalAttackDamage(float dmg)
{
	normalAttackDamage = dmg;
}
float MainCharacter::getChargedAttackDamage()
{
	return chargedAttackDamage;
}
void MainCharacter::setChargedAttackDamage(float dmg)
{
	chargedAttackDamage = dmg;
}
void MainCharacter::setUltimateAttackDamage(float dmg)
{
	ultimateAttackDamage = dmg;
}
float MainCharacter::getUltimateAttackDamage()
{
	return ultimateAttackDamage;
}
float MainCharacter::getAttackDamage(MCAttackType attackType)
{
	if (attackType == MCAttackType::NORMAL) {
		return getNormalAttackDamage();
	}
	else if (attackType == MCAttackType::CHARGED) {
		return getChargedAttackDamage();
	}
	else if (attackType == MCAttackType::ULTIMATE) {
		return getUltimateAttackDamage();
	}
	else {
		return 0.0f;
	}
}
void MainCharacter::setMaxVelocity(float vel)
{
	maxVelocity = vel;
}
float MainCharacter::getVelocity()
{
	return velocity;
}
float MainCharacter::getMaxVelocity()
{
	return maxVelocity;
}
float MainCharacter::getActualHP()
{
	return HP;
}

float MainCharacter::getMaxHP() {
	return maxHP;
}

MCAttackType MainCharacter::getCurrentAttackType()
{
	if (getMCState() == MCState::ChargedAttack) {
		return MCAttackType::CHARGED;
	}
	else if (getMCState() == MCState::Ultimate) {
		return MCAttackType::ULTIMATE;
	}
	else {
		return MCAttackType::NORMAL;
	}
}

Vector2D MainCharacter::getGunPosition()
{
	return gunPosition;
}
void MainCharacter::setGunPosition(Vector2D pos)
{
	gunPosition = pos;
}
void MainCharacter::substractHP(int damage)
{
	HP -= damage;
	HUDManager::getInstance()->changeLife(-damage);
}

float MainCharacter::getReloadTime()
{
	return reloadTime;
}
void MainCharacter::shootHook(Vector2D originPos, Vector2D hookDir)
{
	hookShot->shoot(originPos, hookDir);
}

void MainCharacter::addHP(int life)
{
	HUDManager::getInstance()->changeLife(life);
	HP += life;
	if (HP > maxHP)
		HP = maxHP;
}

void MainCharacter::addMaxHP(float life) {
	HUDManager::getInstance()->setNewHP(life);
	maxHP += life;
	HP += life;
}

void MainCharacter::changeMoney(int mon) {
	money += mon;
	if (money > 9999)
		money = 9999;
	else if (money < 0)
		money = 0;
	HUDManager::getInstance()->ActualizeMoney();
}
///increases both normal and charged damage dealed to enemies
void MainCharacter::addPercentualDamage(float percentage) {
	float newPercentage = (float)1 + (float)(percentage / 100);
	normalAttackDamage = normalAttackDamage * newPercentage;
	chargedAttackDamage = chargedAttackDamage * newPercentage;
}