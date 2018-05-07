#pragma once
#include"RenderComponent.h"
#include"Enemy.h"

class EnemyHUDComponent : public RenderComponent
{
protected:
	Enemy* enemy = nullptr; //the enemy to whom is attached this hud
	Texture* EnemyBar,
		*EnemyBack,
		*EnemySkeleton;
	SDL_Rect destRect, //the back  and skeleton will be painted in the same position and dimension
		HPBarRect, //the rect for the HP
		srcRect;

public:
	EnemyHUDComponent(Enemy* enem);
	~EnemyHUDComponent();
	void lateRender();
};

