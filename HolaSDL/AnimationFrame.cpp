#include "AnimationFrame.h"
#include "GameObject.h"
#include "Texture.h"
#include "Camera.h"
#include "PlayState.h"
#include "Tileset.h"
#include "Game.h"
AnimationFrame::AnimationFrame(Tileset* tileset, GameObject* o,SDL_Rect* srcRect, SDL_Rect destRect, int frameOffsetX, int frameOffsetY, int frameWidth, int frameHeight)
{
	tileSet = tileset;
	gameObject = o;
	this->srcRect = srcRect;
	this->destRect = destRect;
	this->frameOffsetX = frameOffsetX;
	this->frameOffsetY = frameOffsetY;
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;
	
}


AnimationFrame::~AnimationFrame()
{
}

void AnimationFrame::addHurtbox(SDL_Rect rect, int offsetX, int offsetY)
{
	hurtboxes.push_back(rect);
	pair<int, int> aux = { offsetX,offsetY };
	hurtboxOffset.push_back(aux);
}

void AnimationFrame::addHitbox(SDL_Rect rect, int offsetX, int offsetY)
{
	hitboxes.push_back(rect);
	pair<int, int> aux = { offsetX,offsetY };
	hitboxOffset.push_back(aux);
}

void AnimationFrame::addGunPosition(Vector2D gunPos, int offsetX, int offsetY)
{
	gunPosition = gunPos;
	gunPosOffset = { offsetX,offsetY };
}

void AnimationFrame::render(SDL_RendererFlip flip)
{
	//Coloca el sprite correctamente 64 es el tamaño del frame 
	destRect.x = gameObject->getCenterPos().getX() - frameWidth* Game::getGame()->getScale() /2  -
		PlayState::getInstance()->getCamera()->getTransform()->position.getX() 
		+ frameOffsetX;
	destRect.y = gameObject->getCenterPos().getY() - frameHeight * Game::getGame()->getScale() / 2
		- PlayState::getInstance()->getCamera()->getTransform()->position.getY()
		+ frameOffsetY ;
	updateBoxPosition();
	tileSet->getTexture()->render(destRect, srcRect,flip);
}

void AnimationFrame::updateBoxPosition()//Actualiza la posición de las boxes respecto al personaje
{
	Transform* t = gameObject->getTransform();
	for (int i = 0; i < hitboxes.size(); i++) {		//Posiciona las hitbox correctamente
		hitboxes[i].x = gameObject->getCenterPos().getX() - (frameWidth * Game::getGame()->getScale() / 2) + hitboxOffset[i].first;
		hitboxes[i].y = gameObject->getCenterPos().getY() - (frameHeight * Game::getGame()->getScale() / 2) + hitboxOffset[i].second;
	}
	for (int i = 0; i < hurtboxes.size(); i++) {		
		hurtboxes[i].x = gameObject->getCenterPos().getX() - (frameWidth * Game::getGame()->getScale() / 2)+ hurtboxOffset[i].first;
		hurtboxes[i].y = gameObject->getCenterPos().getY() - (frameHeight * Game::getGame()->getScale() / 2) + hurtboxOffset[i].second;
	}
	gunPosition.setX(t->position.getX() + gunPosOffset.first);
	gunPosition.setY(t->position.getY() + gunPosOffset.second);
}
