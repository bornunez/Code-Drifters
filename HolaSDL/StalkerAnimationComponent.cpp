#include "StalkerAnimationComponent.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"


StalkerAnimationComponent::StalkerAnimationComponent(GameObject* o, std::map<const char*, Animation*> anim) : RenderComponent(o)
{
	animations = anim;
	Play("RUN");
}


StalkerAnimationComponent::~StalkerAnimationComponent()
{
}

void StalkerAnimationComponent::render()
{
	currentAnimation->runAnimation();
	debugBoxes();
}

void StalkerAnimationComponent::recieveMessage(std::string msg)
{
	if (msg == "RUN") {
		Play("RUN");
	}
	else if (msg == "RUN") {
		Play("RUN");
	}
}

void StalkerAnimationComponent::debugBoxes()
{
	debugHitbox("Hitbox");
	debugHitbox("Hurtbox");
}

void StalkerAnimationComponent::debugHitbox(string box)
{
	vector<SDL_Rect> boxes;
	if (box == "Hitbox") {
		boxes = currentAnimation->getCurrentFrame()->getHitboxes();
		SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0xff0000ff));//Dibuja las líneas del hitbox en rojo
	}
	else {
		boxes = currentAnimation->getCurrentFrame()->getHurtboxes();
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

void StalkerAnimationComponent::Play(const char * animName)
{
	currentAnimation = animations[animName];
}
