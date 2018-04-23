#include "HUDManager.h"
#include"ResourceManager.h"
#include "Game.h"

HUDManager* HUDManager::instance = nullptr;

HUDManager::HUDManager()
{
	
}

void HUDManager::init(MainCharacter* MC) {
	character = MC;
	gameScale = Game::getGame()->getScale();

	lifeSkeleton = new HUDObject(ResourceManager::getInstance()->getTexture(LifeBorde));
	lifeBar = new HUDObject(ResourceManager::getInstance()->getTexture(LifeBarra));
	lifeBack = new HUDObject(ResourceManager::getInstance()->getTexture(LifeFondo));
	ultSkeleton = new HUDObject(ResourceManager::getInstance()->getTexture(UltBorde));
	ultBar = new HUDObject(ResourceManager::getInstance()->getTexture(UltBarra));
	ultBack = new HUDObject(ResourceManager::getInstance()->getTexture(UltFondo));
	for (int i = 0; i < character->getMaxBullets(); i++) {
		bulletSkeleton.push_back(new HUDObject(ResourceManager::getInstance()->getTexture(HUDBulletBorde)));
		bullets_.push_back(new HUDObject(ResourceManager::getInstance()->getTexture(HUDBulletBarra)));
		bulletBack.push_back(new HUDObject(ResourceManager::getInstance()->getTexture(HUDBulletFondo)));
	}

	ultBack->destRect.w = ultBack->getTexture()->getWidth()*gameScale*0.75;
	ultBack->destRect.h = ultBack->getTexture()->getHeight()*gameScale*0.75;
	ultBack->destRect.x = 50;
	ultBack->destRect.y = 25;

	ultBar->destRect = ultBack->destRect;
	ultBar->destRect.w = ultBar->getTexture()->getWidth()*gameScale*0.75;
	ultBar->destRect.h = ultBar->getTexture()->getHeight()*gameScale*0.75;
	ultSkeleton->destRect = ultBack->destRect;

	lifeBack->destRect = ultBack->destRect;
	lifeBack->destRect.x += ultBar->destRect.w / 2;
	lifeBack->srcRect.x = lifeBack->getTexture()->getWidth() / 3;
	lifeBack->srcRect.w = lifeBack->getTexture()->getWidth() - lifeBack->srcRect.x;
	lifeBack->destRect.w = lifeBack->srcRect.w * gameScale * 0.75;
	lifeBar->destRect = lifeBack->destRect;
	lifeBar->srcRect = lifeBack->srcRect;
	lifeSkeleton->destRect = lifeBack->destRect;
	lifeSkeleton->srcRect = lifeBack->srcRect;

	for (int i = 0; i < bullets_.size(); i++) {

		bulletBack[i]->destRect.w =
			bullets_[i]->destRect.w =
			bulletSkeleton[i]->destRect.w =
			30;
		bulletBack[i]->destRect.h =
			bullets_[i]->destRect.h =
			bulletSkeleton[i]->destRect.h =
			30;

		bulletBack[i]->destRect.x =
			bullets_[i]->destRect.x =
			bulletSkeleton[i]->destRect.x =
			lifeBack->destRect.x + ((bullets_[i]->destRect.w + 10) * i) + 55;

		bulletBack[i]->destRect.y =
			bullets_[i]->destRect.y =
			bulletSkeleton[i]->destRect.y =
			lifeBack->destRect.y + lifeBack->destRect.h - 10;

	}
	//addBullet();
}

HUDManager::~HUDManager()
{
	delete lifeBack,
		lifeBar,
		lifeSkeleton;
	delete ultSkeleton,
		ultBack,
		ultBar;
	for (int i = 0; i < character->getMaxBullets(); i++) {
		delete bulletBack[i],
			bullets_[i],
			bulletSkeleton[i];
	}
}

void HUDManager::render() {
	for (int i = 0; i < bullets_.size(); i++) {
		bulletBack[i]->getTexture()->render(bulletBack[i]->destRect, &bulletBack[i]->srcRect);
		bullets_[i]->getTexture()->render(bullets_[i]->destRect, &bullets_[i]->srcRect);
		bulletSkeleton[i]->getTexture()->render(bulletSkeleton[i]->destRect, &bulletSkeleton[i]->srcRect);
	}
	lifeBack->getTexture()->render(lifeBack->destRect, &lifeBack->srcRect);
	lifeBar->getTexture()->render(lifeBar->destRect, &lifeBar->srcRect);
	lifeSkeleton->getTexture()->render(lifeSkeleton->destRect, &lifeSkeleton->srcRect);

	ultBack->getTexture()->render(ultBack->destRect, &ultBack->srcRect);
	ultBar->getTexture()->render(ultBar->destRect, &ultBar->srcRect);
	ultSkeleton->getTexture()->render(ultSkeleton->destRect, &ultSkeleton->srcRect);
}

void HUDManager::update() {

	float aux = character->getCurrentBullets();
	int currentBullet = (int)aux;
	//the fully charged bullets
	for (int i = 0; i < currentBullet; i++) {
		bullets_[i]->srcRect.y = 0;
		bullets_[i]->srcRect.h = bullets_[i]->getTexture()->getHeight();
		bullets_[i]->destRect.y = bulletSkeleton[i]->destRect.y;
		bullets_[i]->destRect.h = bulletSkeleton[i]->destRect.h;
	}
	//the empty bullets
	if (currentBullet < bullets_.size()) {
		for (int i = currentBullet + 1; i < bullets_.size(); i++) {
			bullets_[i]->srcRect.y = bullets_[i]->getTexture()->getHeight();
			bullets_[i]->srcRect.h = 0;
			bullets_[i]->destRect.y = bulletSkeleton[i]->destRect.y + bulletSkeleton[i]->destRect.h;
			bullets_[i]->destRect.h = 0;
		}
		//the charging bullet
		bullets_[currentBullet]->srcRect.y = bulletBack[currentBullet]->srcRect.h * (1-(aux - currentBullet));
		bullets_[currentBullet]->srcRect.h = bulletBack[currentBullet]->srcRect.h - bullets_[currentBullet]->srcRect.y;

		bullets_[currentBullet]->destRect.y =
			bulletBack[currentBullet]->destRect.y + bulletBack[currentBullet]->destRect.h * (1-(aux - currentBullet));
		bullets_[currentBullet]->destRect.h =
			bulletBack[currentBullet]->destRect.h + bulletBack[currentBullet]->destRect.y - bullets_[currentBullet]->destRect.y;
	}
	//update the ult bar, but without parameter from the character we cant
}

void HUDManager::setNewHP(int newL) {
	lifeBack->destRect.w += newL*gameScale*0.75;
	lifeBack->srcRect.x -= newL;
	lifeBack->srcRect.w += newL;

	lifeBar->destRect.w += newL*gameScale*0.75;
	lifeBar->srcRect.x -= newL;
	lifeBar->srcRect.w += newL;

	lifeSkeleton->destRect.w += newL*gameScale*0.75;
	lifeSkeleton->srcRect.x -= newL;
	lifeSkeleton->srcRect.w += newL;
}

void HUDManager::changeLife(int l) {
	lifeBar->destRect.w += l*gameScale*0.75;
	lifeBar->srcRect.x -= l;
	lifeBar->srcRect.w += l;
	if (lifeBar->destRect.w > lifeBack->destRect.w)
		lifeBar->destRect.w = lifeBack->destRect.w * gameScale * .75;
	else if (lifeBar->destRect.w < 0)
		lifeBar->destRect.w = 0;
}

void HUDManager::addBullet() {
	bulletBack.push_back(new HUDObject(ResourceManager::getInstance()->getTexture(CoinSprite)));
	bulletSkeleton.push_back(new HUDObject(ResourceManager::getInstance()->getTexture(CoinSprite)));
	bullets_.push_back(new HUDObject(ResourceManager::getInstance()->getTexture(CoinSprite)));

	bulletBack.back()->destRect =
		bulletSkeleton.back()->destRect =
		bullets_.back()->destRect =
		bullets_[0]->destRect;

	if (bullets_.size() >= 2)
		bulletBack.back()->destRect.x =
		bullets_.back()->destRect.x =
		bulletSkeleton.back()->destRect.x =
		bullets_[bullets_.size() - 2]->destRect.x + 10 + bullets_[bullets_.size() -2]->destRect.w;
	else {
		bulletBack.back()->destRect.x =
			bullets_.back()->destRect.x =
			bulletSkeleton.back()->destRect.x =
			lifeBack->destRect.x + ((bullets_.back()->destRect.w + 10)) + 65;
	}
}

HUDManager* HUDManager::getInstance() {
	if (instance == nullptr)
		instance = new HUDManager();
	return instance;
}

