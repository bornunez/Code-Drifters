#include "AnimationFrame.h"
#include "GameObject.h"
#include "Texture.h"
#include "Camera.h"
#include "PlayState.h"
#include "Tileset.h"
#include "Game.h"
AnimationFrame::AnimationFrame(Tileset* tileset, GameObject* o,SDL_Rect* srcRect, SDL_Rect destRect, int frameOffsetX, int frameOffsetY)
{
	tileSet = tileset;
	gameObject = o;
	this->srcRect = srcRect;
	this->destRect = destRect;
	this->frameOffsetX = frameOffsetX;
	this->frameOffsetY = frameOffsetY;
	
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

void AnimationFrame::render()
{
	//Coloca el sprite correctamente
	destRect.x = gameObject->getTransform()->position.getX() - gameObject->getTransform()->body.w / 2 -
		PlayState::getInstance()->getCamera()->getTransform()->position.getX() 
		+ frameOffsetX;
	destRect.y = gameObject->getTransform()->position.getY() - gameObject->getTransform()->body.h / 2 
		- PlayState::getInstance()->getCamera()->getTransform()->position.getY()
		+ frameOffsetY ;
	updateBoxPosition();
	tileSet->getTexture()->render(destRect, srcRect);
}

void AnimationFrame::updateBoxPosition()//Actualiza la posición de las boxes respecto al personaje
{
	Transform* t = gameObject->getTransform();
	for (int i = 0; i < hitboxes.size(); i++) {		
		hitboxes[i].x = t->position.getX() + hitboxOffset[i].first;//Le suma a su posición actual el offset que le corresponde
		hitboxes[i].y = t->position.getY() + hitboxOffset[i].second;
	}
	for (int i = 0; i < hurtboxes.size(); i++) {
		hurtboxes[i].x = t->position.getX() + hurtboxOffset[i].first;
		hurtboxes[i].y = t->position.getY() + hurtboxOffset[i].second;
	}
	gunPosition.setX(t->position.getX() + gunPosOffset.first);
	gunPosition.setY(t->position.getY() + gunPosOffset.second);
}
