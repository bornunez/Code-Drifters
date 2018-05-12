#include "EnemyBomb.h"
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
#include "BombComponent.h"
#include "BombAnimationComponent.h"


EnemyBomb::EnemyBomb(MainCharacter* mc) :	Enemy(mc)
{
	type = Bomb;
	transform.body.w = transform.body.h = 0;
	loadAnimations();
	this->addComponent(new BoxRenderer(this, playState->getCamera()));
	this->addComponent(new BombComponent(this, 6, 4.0, 300));
	this->addComponent(new BombAnimationComponent(this, animations));

}



EnemyBomb::~EnemyBomb()
{
}

void EnemyBomb::loadAnimations()
{
	string animationPath = "../Animations/Enemies/BombAnimation.tmx";
	Tileset* tileset = ResourceManager::getInstance()->getEnemyTileset(6);

	Animation* bombLoop = AnimationParser::parseAnimation(tileset, animationPath, "BombLoop", this);
	Animation* death = AnimationParser::parseAnimation(tileset, animationPath, "Death", this);

	

	animations.emplace("BOMBLOOP", bombLoop);
	animations.emplace("DEATH", death);


}




