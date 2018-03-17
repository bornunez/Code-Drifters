#include "MCAnimationComponent.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"
MCAnimationComponent::MCAnimationComponent(GameObject* o, std::map<const char*, Animation*> anim) : RenderComponent(o)
{
	animations = anim;
	Play("IDLE_BOT");
}


MCAnimationComponent::~MCAnimationComponent()
{
}
void MCAnimationComponent::recieveMessage(std::string msg) {
	if (msg == "RUN_LEFT") {
		Play("RUN_LEFT");
	}
	else if (msg == "RUN_RIGHT") {
		Play("RUN_RIGHT");
	}
	else if (msg == "RUN_TOP") {
		Play("RUN_TOP");
	}
	else if (msg == "RUN_BOT") {
		Play("RUN_BOT");
	}
	else if (msg == "IDLE_LEFT") {
		Play("IDLE_LEFT");
	}
	else if (msg == "IDLE_RIGHT") {
		Play("IDLE_RIGHT");
	}
	else if (msg == "IDLE_TOP") {
		Play("IDLE_TOP");
	}
	else if (msg == "IDLE_BOT") {
		Play("IDLE_BOT");
	}
	else if (msg == "ATTACK1_LEFT") {//En las animaciones de ataque, estas se reinician para empezar en el frame 0
		Play("ATTACK1_LEFT");
		currentAnimation->startAnimation();
	}
	else if (msg == "ATTACK2_LEFT") {
		Play("ATTACK2_LEFT");
		currentAnimation->startAnimation();
	}
	else if (msg == "ATTACK3_LEFT") {
		Play("ATTACK3_LEFT");
		currentAnimation->startAnimation();
	}
	else if (msg == "ATTACK1_RIGHT") {
		Play("ATTACK1_RIGHT");
		currentAnimation->startAnimation();
	}
	else if (msg == "ATTACK2_RIGHT") {
		Play("ATTACK2_RIGHT");
		currentAnimation->startAnimation();
	}
	else if (msg == "ATTACK3_RIGHT") {
		Play("ATTACK3_RIGHT");
		currentAnimation->startAnimation();
	}
	else if (msg == "ATTACK1_TOPLEFT") {//En las animaciones de ataque, estas se reinician para empezar en el frame 0
		Play("ATTACK1_TOPLEFT");
		currentAnimation->startAnimation();
	}
	else if (msg == "ATTACK2_TOPLEFT") {
		Play("ATTACK2_TOPLEFT");
		currentAnimation->startAnimation();
	}
	else if (msg == "ATTACK3_TOPLEFT") {
		Play("ATTACK3_TOPLEFT");
		currentAnimation->startAnimation();
	}
	else if (msg == "ATTACK1_TOPRIGHT") {
		Play("ATTACK1_TOPRIGHT");
		currentAnimation->startAnimation();
	}
	else if (msg == "ATTACK2_TOPRIGHT") {
		Play("ATTACK2_TOPRIGHT");
		currentAnimation->startAnimation();
	}
	else if (msg == "ATTACK3_TOPRIGHT") {
		Play("ATTACK3_TOPRIGHT");
		currentAnimation->startAnimation();
	}
	else if (msg == "ATTACK1_BOTLEFT") {//En las animaciones de ataque, estas se reinician para empezar en el frame 0
		Play("ATTACK1_BOTLEFT");
		currentAnimation->startAnimation();
	}
	else if (msg == "ATTACK2_BOTLEFT") {
		Play("ATTACK2_BOTLEFT");
		currentAnimation->startAnimation();
	}
	else if (msg == "ATTACK3_BOTLEFT") {
		Play("ATTACK3_BOTLEFT");
		currentAnimation->startAnimation();
	}
	else if (msg == "ATTACK1_BOTRIGHT") {
		Play("ATTACK1_BOTRIGHT");
		currentAnimation->startAnimation();
	}
	else if (msg == "ATTACK2_BOTRIGHT") {
		Play("ATTACK2_BOTRIGHT");
		currentAnimation->startAnimation();
	}
	else if (msg == "ATTACK3_BOTRIGHT") {
		Play("ATTACK3_BOTRIGHT");
		currentAnimation->startAnimation();
	}
}
void MCAnimationComponent::render()//Renderiza la animación actual, (siempre tiene que haber asignada una animación para que se vea en pantalla)
{
	currentAnimation->runAnimation();
	debugBoxes();
}



void MCAnimationComponent::Play(const char * animName)//Cambia la animación actual que se renderiza
{		
	currentAnimation = animations[animName];	
}

void MCAnimationComponent::debugBoxes()
{
	debugHitbox("Hitbox");
	debugHitbox("Hurtbox");
	
}

void MCAnimationComponent::debugHitbox(string box)
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