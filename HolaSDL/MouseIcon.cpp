#pragma once
#include "MouseIcon.h"
#include "Texture.h"
#include "Game.h"


MouseIcon::MouseIcon(Game* game, string iconFileName){
	this->game = game;
	this->texture = new Texture(game->getRenderer(), iconFileName);
}


void MouseIcon::drawIcon(SDL_Event & e)
{
	if (e.type == SDL_MOUSEMOTION) {
		this->mouseX = e.motion.x;
		this->mouseY = e.motion.y;
	}
	texture->render(mouseX, mouseY);
}
