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
	debugHitbox();
	debugHurtbox();
}

void MCAnimationComponent::debugHitbox()
{
	vector<SDL_Rect> hitboxes = currentAnimation->getCurrentFrame()->getHitboxes();
	for (int i = 0; i < hitboxes.size(); i++) {
		int hitboxX = hitboxes[i].x - PlayState::getInstance()->getCamera()->getTransform()->position.getX();
		int hitboxY = hitboxes[i].y - PlayState::getInstance()->getCamera()->getTransform()->position.getY();
		int hitboxW = hitboxes[i].w;
		int hitboxH = hitboxes[i].h;
		Vector2D hlu(-hitboxW / 2, -hitboxH / 2);
		Vector2D hru(hitboxW / 2, -hitboxH / 2);
		Vector2D hrb(hitboxW / 2, hitboxH / 2);
		Vector2D hlb(-hitboxW / 2, hitboxH / 2);

		SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0xff0000ff));//Dibuja las líneas del hitbox en rojo

		SDL_RenderDrawLine(Game::getGame()->getRenderer(), hlu.getX() + hitboxX + hitboxW / 2, hlu.getY() + hitboxY + hitboxH / 2, hru.getX() + hitboxX + hitboxW / 2,
			hru.getY() + hitboxY + hitboxH / 2);
		SDL_RenderDrawLine(Game::getGame()->getRenderer(), hru.getX() + hitboxX + hitboxW / 2, hru.getY() + hitboxY + hitboxH / 2, hrb.getX() + hitboxX + hitboxW / 2,
			hrb.getY() + hitboxY + hitboxH / 2);
		SDL_RenderDrawLine(Game::getGame()->getRenderer(), hrb.getX() + hitboxX + hitboxW / 2, hrb.getY() + hitboxY + hitboxH / 2, hlb.getX() + hitboxX + hitboxW / 2,
			hlb.getY() + hitboxY + hitboxH / 2);
		SDL_RenderDrawLine(Game::getGame()->getRenderer(), hlb.getX() + hitboxX + hitboxW / 2, hlb.getY() + hitboxY + hitboxH / 2, hlu.getX() + hitboxX + hitboxW / 2,
			hlu.getY() + hitboxY + hitboxH / 2);
	}
}

void MCAnimationComponent::debugHurtbox()
{
	vector<SDL_Rect> hurtboxes = currentAnimation->getCurrentFrame()->getHurtboxes();
	for (int i = 0; i < hurtboxes.size(); i++) {
		int hurtboxX = hurtboxes[i].x - PlayState::getInstance()->getCamera()->getTransform()->position.getX();
		int hurtboxY = hurtboxes[i].y - PlayState::getInstance()->getCamera()->getTransform()->position.getY();
		int hurtboxW = hurtboxes[i].w;
		int hurtboxH = hurtboxes[i].h;
		Vector2D hlu(-hurtboxW / 2, -hurtboxH / 2);
		Vector2D hru(hurtboxW / 2, -hurtboxH / 2);
		Vector2D hrb(hurtboxW / 2, hurtboxH / 2);
		Vector2D hlb(-hurtboxW / 2, hurtboxH / 2);

		SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0x00ff00ff));//Dibuja las líneas del hurtbox en verde

		SDL_RenderDrawLine(Game::getGame()->getRenderer(), hlu.getX() + hurtboxX + hurtboxW / 2, hlu.getY() + hurtboxY + hurtboxH / 2, hru.getX() + hurtboxX + hurtboxW / 2,
			hru.getY() + hurtboxY + hurtboxH / 2);
		SDL_RenderDrawLine(Game::getGame()->getRenderer(), hru.getX() + hurtboxX + hurtboxW / 2, hru.getY() + hurtboxY + hurtboxH / 2, hrb.getX() + hurtboxX + hurtboxW / 2,
			hrb.getY() + hurtboxY + hurtboxH / 2);
		SDL_RenderDrawLine(Game::getGame()->getRenderer(), hrb.getX() + hurtboxX + hurtboxW / 2, hrb.getY() + hurtboxY + hurtboxH / 2, hlb.getX() + hurtboxX + hurtboxW / 2,
			hlb.getY() + hurtboxY + hurtboxH / 2);
		SDL_RenderDrawLine(Game::getGame()->getRenderer(), hlb.getX() + hurtboxX + hurtboxW / 2, hlb.getY() + hurtboxY + hurtboxH / 2, hlu.getX() + hurtboxX + hurtboxW / 2,
			hlu.getY() + hurtboxY + hurtboxH / 2);
	}

}

