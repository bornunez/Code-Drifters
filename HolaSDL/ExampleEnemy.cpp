#include "ExampleEnemy.h"
//#include "ChaseComponent.h"
//#include "Game.h"
//#include "Enemy.h"
//#include "Camera.h"
//
//
//
//
//ExampleEnemy::ExampleEnemy(Game* game, MainCharacter* mc, Transform t) :
//	Enemy(game, mc, t)
//{
//	
//	addComponent(new ChaseComponent(this, getMC(), 0.1));
//}
//
//ExampleEnemy::ExampleEnemy(Game* game, MainCharacter* mc, int x, int y, int w, int h) :
//	Enemy(game, mc, x, y, w, h)
//{
//
//	addComponent(new ChaseComponent(this, mc, 0.1));
//}
//
//
//ExampleEnemy::~ExampleEnemy()
//{
//}
//
//void ExampleEnemy::render() {
//	float auxX = transform.position.getX() - getGame()->getCamera()->getTransform()->position.getX();
//	float auxY = transform.position.getY() - getGame()->getCamera()->getTransform()->position.getY();
//	SDL_Rect rect RECT(auxX, auxY, transform.body.w, transform.body.h);
//	SDL_SetRenderDrawColor(game->getRenderer(), COLOR(0xfff00fff));
//	SDL_RenderFillRect(game->getRenderer(), &rect);
//	SDL_SetRenderDrawColor(game->getRenderer(), COLOR(0x000ff0ff));
//}
//
