#include "MCAnimationComponent.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"
MCAnimationComponent::MCAnimationComponent(GameObject* o, std::map<const char*, Animation*> anim) : RenderComponent(o)
{
	animations = anim;
	Play("WALK_LEFT");
}


MCAnimationComponent::~MCAnimationComponent()
{
}
void MCAnimationComponent::recieveMessage(std::string msg) {
	if (msg == "WALK_LEFT") {
		Play("WALK_LEFT");
	}
	else if(msg == "WALK_RIGHT") {
		Play("WALK_RIGHT");
	}
}
void MCAnimationComponent::render()
{

	currentAnimation->runAnimation();
	debugBoxes();
}



void MCAnimationComponent::Play(const char * animName)
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
	int hitboxX = currentAnimation->getCurrentFrame()->getHitbox().x - PlayState::getInstance()->getCamera()->getTransform()->position.getX();
	int hitboxY = currentAnimation->getCurrentFrame()->getHitbox().y - PlayState::getInstance()->getCamera()->getTransform()->position.getY();
	int hitboxW = currentAnimation->getCurrentFrame()->getHitbox().w;
	int hitboxH = currentAnimation->getCurrentFrame()->getHitbox().h;
	Vector2D hlu(-currentAnimation->getCurrentFrame()->getHitbox().w / 2, -currentAnimation->getCurrentFrame()->getHitbox().h / 2);
	Vector2D hru(currentAnimation->getCurrentFrame()->getHitbox().w / 2, -currentAnimation->getCurrentFrame()->getHitbox().h / 2);
	Vector2D hrb(currentAnimation->getCurrentFrame()->getHitbox().w / 2, currentAnimation->getCurrentFrame()->getHitbox().h / 2);
	Vector2D hlb(-currentAnimation->getCurrentFrame()->getHitbox().w / 2, currentAnimation->getCurrentFrame()->getHitbox().h / 2);

	SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0xff0000ff));//Dibuja las líneas del hitbox en verde
	SDL_RenderDrawLine(Game::getGame()->getRenderer(), hlu.getX() + hitboxX + hitboxW / 2, hlu.getY() + hitboxY + hitboxH / 2, hru.getX() + hitboxX + hitboxW / 2,
		hru.getY() + hitboxY + hitboxH / 2);
	SDL_RenderDrawLine(Game::getGame()->getRenderer(), hru.getX() + hitboxX + hitboxW / 2, hru.getY() + hitboxY + hitboxH / 2, hrb.getX() + hitboxX + hitboxW / 2,
		hrb.getY() + hitboxY + hitboxH / 2);
	SDL_RenderDrawLine(Game::getGame()->getRenderer(), hrb.getX() + hitboxX + hitboxW / 2, hrb.getY() + hitboxY + hitboxH / 2, hlb.getX() + hitboxX + hitboxW / 2,
		hlb.getY() + hitboxY + hitboxH / 2);
	SDL_RenderDrawLine(Game::getGame()->getRenderer(), hlb.getX() + hitboxX + hitboxW / 2, hlb.getY() + hitboxY + hitboxH / 2, hlu.getX() + hitboxX + hitboxW / 2,
		hlu.getY() + hitboxY + hitboxH / 2);
}

void MCAnimationComponent::debugHurtbox()
{
	int hurtboxX = currentAnimation->getCurrentFrame()->getHurtbox().x - PlayState::getInstance()->getCamera()->getTransform()->position.getX();
	int hurtboxY = currentAnimation->getCurrentFrame()->getHurtbox().y - PlayState::getInstance()->getCamera()->getTransform()->position.getY();
	int hurtboxW = currentAnimation->getCurrentFrame()->getHurtbox().w;
	int hurtboxH = currentAnimation->getCurrentFrame()->getHurtbox().h;
	Vector2D hlu(-currentAnimation->getCurrentFrame()->getHurtbox().w / 2, -currentAnimation->getCurrentFrame()->getHurtbox().h / 2);
	Vector2D hru(currentAnimation->getCurrentFrame()->getHurtbox().w / 2, -currentAnimation->getCurrentFrame()->getHurtbox().h / 2);
	Vector2D hrb(currentAnimation->getCurrentFrame()->getHurtbox().w / 2, currentAnimation->getCurrentFrame()->getHurtbox().h / 2);
	Vector2D hlb(-currentAnimation->getCurrentFrame()->getHurtbox().w / 2, currentAnimation->getCurrentFrame()->getHurtbox().h / 2);

	SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0x00ff00ff));//Dibuja las líneas del hurtbox en rojo
	SDL_RenderDrawLine(Game::getGame()->getRenderer(), hlu.getX() + hurtboxX + hurtboxW / 2, hlu.getY() + hurtboxY + hurtboxH / 2, hru.getX() + hurtboxX + hurtboxW / 2,
		hru.getY() + hurtboxY + hurtboxH / 2);
	SDL_RenderDrawLine(Game::getGame()->getRenderer(), hru.getX() + hurtboxX + hurtboxW / 2, hru.getY() + hurtboxY + hurtboxH / 2, hrb.getX() + hurtboxX + hurtboxW / 2,
		hrb.getY() + hurtboxY + hurtboxH / 2);
	SDL_RenderDrawLine(Game::getGame()->getRenderer(), hrb.getX() + hurtboxX + hurtboxW / 2, hrb.getY() + hurtboxY + hurtboxH / 2, hlb.getX() + hurtboxX + hurtboxW / 2,
		hlb.getY() + hurtboxY + hurtboxH / 2);
	SDL_RenderDrawLine(Game::getGame()->getRenderer(), hlb.getX() + hurtboxX + hurtboxW / 2, hlb.getY() + hurtboxY + hurtboxH / 2, hlu.getX() + hurtboxX + hurtboxW / 2,
		hlu.getY() + hurtboxY + hurtboxH / 2);
}

