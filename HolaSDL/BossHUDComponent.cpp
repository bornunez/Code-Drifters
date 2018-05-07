#include "BossHUDComponent.h"
#include"ResourceManager.h"
#include"Game.h"


BossHUDComponent::BossHUDComponent(MasterBoss* bossy) : RenderComponent(bossy)
{
	boss = bossy;

	bossBack = new HUDObject(ResourceManager::getInstance()->getTexture(EnemyHUDFondo));//cambiar las textures
	bossBarBack = new HUDObject(ResourceManager::getInstance()->getTexture(BossSecondFill));
	bossBar = new HUDObject(ResourceManager::getInstance()->getTexture(EnemyHUDBarra));
	bossSkeleton = new HUDObject(ResourceManager::getInstance()->getTexture(EnemyHUDBorde));
	//el resto de texturas de los demas hudobjects

	bossBack->destRect.x = Game::getGame()->getWinW() / 8;
	bossBack->destRect.y = Game::getGame()->getWinH() * 4 / 5;
	bossBack->destRect.w = Game::getGame()->getWinW() * 3 / 4;
	bossBack->destRect.h = Game::getGame()->getWinH() / 12;

	bossBack->srcRect.x = bossBack->srcRect.y = 0;
	bossBack->srcRect.w = bossBack->getTexture()->getWidth();
	bossBack->srcRect.h = bossBack->getTexture()->getHeight();
	//supposing all the textures have the same dimensions
	bossBar->srcRect = bossBarBack->srcRect = bossSkeleton->srcRect = bossBack->srcRect;
	
	bossBar->destRect = bossBarBack->destRect = bossSkeleton->destRect = bossBack->destRect;
}

void BossHUDComponent::lateRender() {
	if (boss->getLife() > 0) {
		bossBar->destRect.w = (boss->getLife() * bossBack->destRect.w) / boss->getMaxHP();
		if (bossBarBack->destRect.w > bossBar->destRect.w) bossBarBack->destRect.w--;

		bossBack->getTexture()->render(bossBack->destRect, &bossBack->srcRect);
		bossBarBack->getTexture()->render(bossBarBack->destRect, &bossBarBack->srcRect);
		bossBar->getTexture()->render(bossBar->destRect, &bossBar->srcRect);
		bossSkeleton->getTexture()->render(bossSkeleton->destRect, &bossSkeleton->srcRect);
	}
}

BossHUDComponent::~BossHUDComponent()
{
	delete bossBack,
		bossBar,
		bossBarBack,
		bossSkeleton;
}
