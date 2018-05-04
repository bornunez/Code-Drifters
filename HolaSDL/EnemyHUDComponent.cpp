#include "EnemyHUDComponent.h"
#include"ResourceManager.h"


EnemyHUDComponent::EnemyHUDComponent(Enemy* enem) : RenderComponent(enem)
{
	enemy = enem;
	//HP = maxHP = enemy->getLife();
	destRect.x = enemy->getCenterPos().getX() - 15;
	destRect.y = enemy->getCenterPos().getY() + 5;
	destRect.w = 35;
	destRect.h = 15;

	HPBarRect = destRect;

	EnemyBack = ResourceManager::getInstance()->getTexture(LifeFondo);
	EnemyBar = ResourceManager::getInstance()->getTexture(LifeBarra);
	EnemySkeleton = ResourceManager::getInstance()->getTexture(LifeBorde);

	srcRect.x = srcRect.y = 0;
	srcRect.w = EnemyBack->getWidth();
	srcRect.h = EnemyBack->getHeight();
}


EnemyHUDComponent::~EnemyHUDComponent()
{
}

void EnemyHUDComponent::render() {
	if (enemy->getLife() > 0) {
		HPBarRect.w = (enemy->getLife() * destRect.w) / enemy->getMaxLife();
		//to keep the hud in the same relative pos to their enemy
		destRect.x = HPBarRect.x = enemy->getDisplayCenterPos().getX() - 15;
		destRect.y = HPBarRect.y = enemy->getDisplayCenterPos().getY() + 30;
		EnemyBack->render(destRect, &srcRect);
		EnemyBar->render(HPBarRect, &srcRect);
		EnemySkeleton->render(destRect, &srcRect);
	}
}