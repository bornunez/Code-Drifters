#include "HUDManager.h"
#include"ResourceManager.h"


HUDManager::HUDManager(MainCharacter* MC)
{
	character = MC;

	lifeSkeleton = new HUDObject(ResourceManager::getInstance()->getTexture(CoinSprite));
	lifeBar = new HUDObject();
	lifeBack = new HUDObject();
	ultSkeleton = new HUDObject();
	ultBar = new HUDObject();
	ultBack = new HUDObject();
	for (int i = 0; i < character->getMaxBullets(); i++) {
		bulletSkeleton.push_back(new HUDObject());
		bullets_.push_back(new HUDObject());
		bulletBack.push_back(new HUDObject());
	}
	lifeBack->destRect.w = lifeBack->getTexture()->getFrameWidth();;
	lifeBack->destRect.h = lifeSkeleton->getTexture()->getFrameHeight();
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
		bulletBack[i]->render();
		bullets_[i]->render();
		bulletSkeleton[i]->render();
	}
	lifeBack->render();
	lifeBar->render();
	lifeSkeleton->render();
	ultBack->render();
	ultBar->render();
	ultSkeleton->render();
}

void HUDManager::update() {
	
}

void HUDManager::setNewHP(float newL) {

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
