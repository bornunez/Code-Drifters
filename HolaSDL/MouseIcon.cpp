#pragma once
#include "MouseIcon.h"
#include "Texture.h"
#include "Game.h"


MouseIcon::MouseIcon(string iconFileName){
	this->game = Game::getGame();
	this->texture = new Texture(game->getRenderer(), iconFileName);
}

MouseIcon::~MouseIcon()
{
	delete texture;
}


void MouseIcon::drawIcon(SDL_Event & e)
{
	if (e.type == SDL_MOUSEMOTION) {
		this->mouseX = e.motion.x;
		this->mouseY = e.motion.y;
	}
	texture->render(mouseX - texture->getWidth()/2, mouseY - texture->getHeight()/2);
}
