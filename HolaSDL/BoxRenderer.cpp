#include "BoxRenderer.h"
#include <algorithm>
#include "Transform.h"
#include "GameObject.h"
#include "Game.h"
#include "Animation.h"
#include "PlayState.h"
#include "Camera.h"
#include "Component.h"
BoxRenderer::BoxRenderer(GameObject* o, GameObject* camera) : RenderComponent(o), camera(camera)
{
}


BoxRenderer::~BoxRenderer()
{
}

void BoxRenderer::render()
{
	debugBoxes();
}
void BoxRenderer::debugBoxes()
{
	debugHitbox("Hitbox");
	debugHitbox("Hurtbox");
	debugGunPosition();
}

void BoxRenderer::debugHitbox(string box)
{	
	vector<SDL_Rect> boxes;
	if (box == "Hitbox") {
		boxes = gameObject->getCurrentAnimation()->getCurrentFrame()->getHitboxes();
		SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0xff0000ff));//Dibuja las líneas del hitbox en rojo
	}
	else {
		boxes = gameObject->getCurrentAnimation()->getCurrentFrame()->getHurtboxes();
		SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0x00ff00ff));//Dibuja las líneas del hurtbox en verde
	}
	for (int i = 0; i < boxes.size(); i++) {
		int boxX = boxes[i].x - PlayState::getInstance()->getCamera()->getTransform()->position.getX();
		int boxY = boxes[i].y - PlayState::getInstance()->getCamera()->getTransform()->position.getY();
		int boxW = boxes[i].w;
		int boxH = boxes[i].h;
		Vector2D hlu(-boxW / 2, -boxH / 2);
		Vector2D hru(boxW / 2, -boxH / 2);
		Vector2D hrb(boxW / 2, boxH / 2);
		Vector2D hlb(-boxW / 2, boxH / 2);



		SDL_RenderDrawLine(Game::getGame()->getRenderer(), hlu.getX() + boxX + boxW / 2, hlu.getY() + boxY + boxH / 2, hru.getX() + boxX + boxW / 2,
			hru.getY() + boxY + boxH / 2);
		SDL_RenderDrawLine(Game::getGame()->getRenderer(), hru.getX() + boxX + boxW / 2, hru.getY() + boxY + boxH / 2, hrb.getX() + boxX + boxW / 2,
			hrb.getY() + boxY + boxH / 2);
		SDL_RenderDrawLine(Game::getGame()->getRenderer(), hrb.getX() + boxX + boxW / 2, hrb.getY() + boxY + boxH / 2, hlb.getX() + boxX + boxW / 2,
			hlb.getY() + boxY + boxH / 2);
		SDL_RenderDrawLine(Game::getGame()->getRenderer(), hlb.getX() + boxX + boxW / 2, hlb.getY() + boxY + boxH / 2, hlu.getX() + boxX + boxW / 2,
			hlu.getY() + boxY + boxH / 2);
		
	}
}

void BoxRenderer::debugGunPosition()
{

	
	SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0x0000ffff));//Dibuja el punto en azul
	Vector2D gunPos = gameObject->getCurrentAnimation()->getCurrentFrame()->getGunPosition();	
	int PX = gunPos.getX() - PlayState::getInstance()->getCamera()->getTransform()->position.getX();
	int PY = gunPos.getY() - PlayState::getInstance()->getCamera()->getTransform()->position.getY();
	SDL_RenderDrawPoint(Game::getGame()->getRenderer(), PX, PY);

	SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0xff0000ff));//Dibuja el punto en azul
	Vector2D gunPos1 = gameObject->getDisplayCenterPos();
	int PX1 = gunPos1.getX();
	int PY1 = gunPos1.getY();
	SDL_RenderDrawPoint(Game::getGame()->getRenderer(), PX1, PY1);
}
