#include "HUDManager.h"
#include"ResourceManager.h"
#include "Game.h"

HUDManager* HUDManager::instance = nullptr;

HUDManager::HUDManager()
{
	
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
	lifeSkeleton->getTexture()->render(lifeBack->destRect, &lifeBar->srcRect);

	ultBack->getTexture()->render(ultBack->destRect, &ultBack->srcRect);
	ultBar->getTexture()->render(ultBar->destRect, &ultBar->srcRect);
	ultSkeleton->getTexture()->render(ultSkeleton->destRect, &ultSkeleton->srcRect);
}

void HUDManager::update() {

	float aux = character->getCurrentBullets();
	int currentBullet = (int)aux - 1;
	//the fully charged bullets
	for (int i = 0; i < currentBullet; i++) {
		bullets_[i]->srcRect.y = 0;
		bullets_[i]->srcRect.h = bullets_[i]->getTexture()->getHeight();
		bullets_[i]->destRect.y = bulletSkeleton[i]->destRect.y;
		bullets_[i]->destRect.h = bulletSkeleton[i]->destRect.h;
	}
	//the empty bullets
	for (int i = currentBullet + 1; i < bullets_.size(); i++) {
		bullets_[i]->srcRect.y = bullets_[i]->getTexture()->getHeight();
		bullets_[i]->srcRect.h = 0;
		bullets_[i]->destRect.y = bulletSkeleton[i]->destRect.y + bulletSkeleton[i]->destRect.h;
		bullets_[i]->destRect.h = 0;
	}
	//the charging bullet
	bullets_[currentBullet]->srcRect.y = bullets_[currentBullet]->srcRect.h * (aux - (currentBullet + 1));
	bullets_[currentBullet]->srcRect.h = bulletSkeleton[currentBullet]->srcRect.h - bullets_[currentBullet]->srcRect.y;

	bullets_[currentBullet]->destRect.y = bullets_[currentBullet]->destRect.h * (aux - (currentBullet + 1));
	bullets_[currentBullet]->destRect.h =
		bulletSkeleton[currentBullet]->destRect.h + bulletSkeleton[currentBullet]->destRect.y -bullets_[currentBullet]->destRect.y;
	//update the ult bar, but without parameter from the character we cant
}

void HUDManager::setNewHP(float newL) {
	lifeBack->destRect.w += newL;
	lifeBar->destRect.w += newL;
	lifeSkeleton->destRect.w += newL;
}

void HUDManager::addBullet() {
	bulletBack.push_back(new HUDObject());
	bulletSkeleton.push_back(new HUDObject());
	bullets_.push_back(new HUDObject());

	bulletBack.back()->destRect =
		bulletSkeleton.back()->destRect =
		bullets_.back()->destRect =
		bullets_[0]->destRect;

	if (bullets_.size() >= 2)
		bulletBack.back()->destRect.x =
		bullets_.back()->destRect.x =
		bulletSkeleton.back()->destRect.x =
		bullets_[bullets_.size() - 2]->destRect.x + 75;
	else {
		bulletBack.back()->destRect.x =
			bullets_.back()->destRect.x =
			bulletSkeleton.back()->destRect.x =
			lifeBack->destRect.x;
	}
}

void HUDManager::changeLife(float l) {
	lifeBar->destRect.w += l;
	if (lifeBar->destRect.w > lifeBack->destRect.w)
		lifeBar->destRect.w = lifeBack->destRect.w;
	else if (lifeBar->destRect.w < 0)
		lifeBar->destRect.w = 0;
}

HUDManager* HUDManager::getInstance() {
	if (instance == nullptr)
		instance = new HUDManager();
	return instance;
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
		bulletSkeleton.push_back(new HUDObject(ResourceManager::getInstance()->getTexture(CoinSprite)));
		bullets_.push_back(new HUDObject(ResourceManager::getInstance()->getTexture(CoinSprite)));
		bulletBack.push_back(new HUDObject(ResourceManager::getInstance()->getTexture(CoinSprite)));
	}
	lifeBack->destRect.w = lifeBack->getTexture()->getFrameWidth()*gameScale * 0.75;
	lifeBack->destRect.h = lifeSkeleton->getTexture()->getFrameHeight()*gameScale * 0.75;
	lifeBack->destRect.x = 50;
	lifeBack->destRect.y = 25;

	lifeBar->destRect = lifeBack->destRect;
	lifeSkeleton->destRect = lifeBack->destRect;

	ultBack->destRect = lifeBack->destRect;
	ultBar->destRect = lifeBack->destRect;
	ultSkeleton->destRect = lifeBack->destRect;


	for (int i = 0; i < bullets_.size(); i++) {
		bulletBack[i]->destRect.x =
			bullets_[i]->destRect.x =
			bulletSkeleton[i]->destRect.x =
			lifeBack->destRect.x + (75 * i);

		bulletBack[i]->destRect.y =
			bullets_[i]->destRect.y =
			bulletSkeleton[i]->destRect.y =
			lifeBack->destRect.y + lifeBack->destRect.h + 50;

		bulletBack[i]->destRect.w =
			bullets_[i]->destRect.w =
			bulletSkeleton[i]->destRect.w =
			bulletBack[i]->destRect.h =
			bullets_[i]->destRect.h =
			bulletSkeleton[i]->destRect.h =
			50;
	}
}