#include "HUDManager.h"
#include"ResourceManager.h"
#include "Game.h"
#include "PlayState.h"

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

	ultBack->destRect.w = ultBack->getTexture()->getWidth()*gameScale*0.7;
	ultBack->destRect.h = ultBack->getTexture()->getHeight()*gameScale*0.7;
	ultBack->destRect.x = 50;
	ultBack->destRect.y = 25;

	ultBar->destRect = ultBack->destRect;
	ultBar->destRect.w = ultBar->getTexture()->getWidth()*gameScale*0.75;
	ultBar->destRect.h = ultBar->getTexture()->getHeight()*gameScale*0.75;
	ultSkeleton->destRect = ultBack->destRect;

	lifeBack->destRect = ultBack->destRect;
	lifeBack->destRect.x += ultBar->destRect.w*3/4;
	lifeBack->srcRect.x = lifeBack->getTexture()->getWidth() / 3;
	lifeBack->srcRect.w = lifeBack->getTexture()->getWidth() - lifeBack->srcRect.x;
	lifeBack->destRect.w = lifeBack->srcRect.w * gameScale * 0.65;
	lifeBar->destRect = lifeBack->destRect;
	lifeBar->srcRect = lifeBack->srcRect;
	lifeSkeleton->destRect = lifeBack->destRect;
	lifeSkeleton->srcRect = lifeBack->srcRect;

	lifeUnit = lifeBack->destRect.w / PlayState::getInstance()->getMainCharacter()->getMaxHP();

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

	moneyFont = new Font("..\\images\\Polentical Neon Bold.ttf", 50);
	moneyTex = new Texture(Game::getGame()->getRenderer());
	moneyColor.a = 255;
	moneyColor.r = moneyColor.g = moneyColor.b = 255;
	moneyTex->loadFromText(to_string(PlayState::getInstance()->getMainCharacter()->getMoney()), *moneyFont, moneyColor);
	moneyDestRect.h  = 50;
	moneyDestRect.w = (to_string(PlayState::getInstance()->getMainCharacter()->getMoney()).size() * 15);
	moneyDestRect.y = Game::getGame()->getWinH() / 5;
	//cout << to_string(PlayState::getInstance()->getMainCharacter()->getMoney()).size() << endl;
	moneyDestRect.x = Game::getGame()->getWinW() / 15 - ((to_string(PlayState::getInstance()->getMainCharacter()->getMoney()).size() - 1) * 15) + 50;
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

	moneyTex->render(moneyDestRect);
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
	//update the ult bar
	ultBar->srcRect.y = ultBack->srcRect.h * (1-(character->getUltiCharge() / 100));
	ultBar->srcRect.h = ultBack->srcRect.h - ultBar->srcRect.y;

	ultBar->destRect.y = ultBack->destRect.y + ultBack->destRect.h * (1-(character->getUltiCharge() / 100));
	ultBar->destRect.h = ultBack->destRect.h + ultBack->destRect.y - ultBar->destRect.y;
}
///method which can increase maxHP or low it
void HUDManager::setNewHP(int newL) {
	lifeBack->destRect.w += (int)((float)(newL*lifeUnit));
	lifeBack->srcRect.x -= newL;
	lifeBack->srcRect.w += newL;

	lifeBar->destRect.w += (int)((float)(newL*lifeUnit));
	lifeBar->srcRect.x -= newL;
	lifeBar->srcRect.w += newL;

	lifeSkeleton->destRect.w += (int)((float)(newL*lifeUnit));
	lifeSkeleton->srcRect.x -= newL;
	lifeSkeleton->srcRect.w += newL;
}
///method that changes actual life, but in maxHP interval
void HUDManager::changeLife(int l) {
	//cout << lifeBar->destRect.w << "londgi" << endl;
	lifeBar->destRect.w += (int)((float)(l * lifeUnit));
	lifeBar->srcRect.x -= l;
	lifeBar->srcRect.w += l;
	if (lifeBar->destRect.w > lifeBack->destRect.w) {
		lifeBar->destRect.w = lifeBack->destRect.w;
		lifeBar->srcRect = lifeBack->srcRect;
	}
	else if (lifeBar->destRect.w < 0)
		lifeBar->destRect.w = 0;
}

void HUDManager::addBullet() {
	bulletBack.push_back(new HUDObject(ResourceManager::getInstance()->getTexture(HUDBulletFondo)));
	bulletSkeleton.push_back(new HUDObject(ResourceManager::getInstance()->getTexture(HUDBulletBorde)));
	bullets_.push_back(new HUDObject(ResourceManager::getInstance()->getTexture(HUDBulletBarra)));

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

void HUDManager::ActualizeMoney() {
	moneyTex->loadFromText(to_string(PlayState::getInstance()->getMainCharacter()->getMoney()), *moneyFont, moneyColor);
	moneyDestRect.x = Game::getGame()->getWinW() / 15 - ((to_string(PlayState::getInstance()->getMainCharacter()->getMoney()).size() - 1) * 15) + 50;
	moneyDestRect.w = (to_string(PlayState::getInstance()->getMainCharacter()->getMoney()).size() * 15);	
}

