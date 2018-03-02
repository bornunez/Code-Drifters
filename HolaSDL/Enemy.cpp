#include "Enemy.h"
#include "Game.h"


Enemy::Enemy(Game* game, MainCharacter* mc, Transform t) : GameObject(game)
{
	mainCharacter = mc;
	transform.position.setX(t.position.getX());
	transform.position.setY(t.position.getY());
	transform.body.w = t.body.w;
	transform.body.h = t.body.h;

}
Enemy::Enemy(Game* game, MainCharacter* mc, int x, int y, int w, int h) : GameObject(game)
{
	mainCharacter = mc;
	transform.position.setX(x);
	transform.position.setY(y);
	transform.body.w = w;
	transform.body.h = h;
}

Enemy::~Enemy()
{
}

void Enemy::render() {
	float auxX = transform.position.getX() - getGame()->getCamera()->getTransform()->position.getX();
	float auxY = transform.position.getY() - getGame()->getCamera()->getTransform()->position.getY();
	SDL_Rect rect RECT(auxX, auxY, transform.body.w, transform.body.h);
	SDL_SetRenderDrawColor(game->getRenderer(), COLOR(0xfff00fff));
	SDL_RenderFillRect(game->getRenderer(), &rect);
	SDL_SetRenderDrawColor(game->getRenderer(), COLOR(0x000ff0ff));
}

GameObject* Enemy::getMC() {
	return mainCharacter;
}


void Enemy::receiveDamage(int damage) {
	life -= damage;
	if (life <= 0) {
		onDestroy();
	}
}

void Enemy::onDestroy() {
	//droppear dinero etc
}
