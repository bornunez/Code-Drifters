#include "MainCharacter.h"
#include "Game.h"


MainCharacter::MainCharacter(Game* game) : GameObject(game)
{
}


MainCharacter::~MainCharacter()
{
}
void MainCharacter::render(){
	SDL_Rect rect RECT(transform.position.getX(),transform.position.getY(),transform.body.w,transform.body.h);
	SDL_SetRenderDrawColor(game->getRenderer(), COLOR(0xff00ffff));
	SDL_RenderFillRect(game->getRenderer(), &rect);
}
