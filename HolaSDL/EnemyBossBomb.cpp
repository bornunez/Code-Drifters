#include "EnemyBossBomb.h"
#include "ExampleRender.h"
#include "Game.h"
#include "Enemy.h"
#include "Camera.h"
#include "PlayState.h"
#include "GameObject.h"
#include "ComponentContainer.h"
#include "EnemyManager.h"
#include "AnimationParser.h"
#include "Tileset.h"
#include "ResourceManager.h"
#include "BoxRenderer.h"
#include "BossBombComponent.h"
#include "BossBombAnimationComponent.h"


EnemyBossBomb::EnemyBossBomb(MainCharacter* mc) :	Enemy(mc)
{
	type = Bomb;
	transform.body.w = transform.body.h = 0;
	loadAnimations();
	this->addComponent(new BoxRenderer(this, playState->getCamera()));
	this->addComponent(new BossBombComponent(this, 6, 4.0, 300));
	this->addComponent(new BossBombAnimationComponent(this, animations));

}



EnemyBossBomb::~EnemyBossBomb()
{
}

void EnemyBossBomb::loadAnimations()
{
	string animationPath = "../Animations/Enemies/BombAnimation.tmx";
	Tileset* tileset = ResourceManager::getInstance()->getEnemyTileset(6);

	Animation* bossBomb = AnimationParser::parseAnimation(tileset, animationPath, "BossBomb", this);
	Animation* death = AnimationParser::parseAnimation(tileset, animationPath, "Death", this);

	

	animations.emplace("BOSSBOMB", bossBomb);
	animations.emplace("DEATH", death);


}




