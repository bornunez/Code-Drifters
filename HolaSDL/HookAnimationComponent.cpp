#include "HookAnimationComponent.h"
#include "GameObject.h"
#include "PlayState.h"
#include "MainCharacter.h"
#include "Camera.h"
#include "Game.h"
#include "Hook.h"


HookAnimationComponent::HookAnimationComponent(Hook* o, Texture* hookChainTex, Texture* hookChainFailTex,  Texture* hookHeadTex, double angle, int fps, SDL_RendererFlip flip) : RenderComponent(static_cast<GameObject*>(o))
{
	hook = o;
	this->hookChainTex = hookChainTex;
	this->hookChainFailTex = hookChainFailTex;
	this->hookHeadTex = hookHeadTex;
	this->angle = angle;
	this->fps = fps;
	this->flip = flip;
	hookFailAnim = new Timer();
	
}

void HookAnimationComponent::receiveMessage(Message * msg)
{
	switch (msg->id) {
		case HOOK_EMPTY:
		hookFailAnim->restart();
		hookFailSprite = 0;
		break;
	}
}


void HookAnimationComponent::render()
{
	if (hook->isActive()) {
		if (hook->getHookStatus() == HookStatus::EXTEND || hook->getHookStatus() == HookStatus::MOVE_ENEMY || hook->getHookStatus() == HookStatus::MOVE_MC) {

			renderHookChains();
			renderHookHead();
		}
		else {
			renderHookFail();
		}
	}

}

void HookAnimationComponent::renderHookHead()
{
	Uint32 ticks = SDL_GetTicks();

	float displayX = hook->getDisplayCenterPos().getX();
	float displayY = hook->getDisplayCenterPos().getY();

	Uint32 sprite = (ticks / fps) % hookHeadTex->getNumCols();
	SDL_Rect srcrect = { sprite * hookHeadTex->getFrameWidth(), animationNumber * hookHeadTex->getFrameHeight(), hookHeadTex->getFrameWidth(), hookHeadTex->getFrameHeight() };
	SDL_Rect dstrect = { displayX - hook->getTransform()->body.w / 2, displayY - hook->getTransform()->body.h / 2, hook->getTransform()->body.w,  hook->getTransform()->body.h};
	angle = hook->getAngle();

	SDL_Point center;
	center.x = dstrect.w / 2;
	center.y = dstrect.h / 2;

	hookHeadTex->render(dstrect, angle, &center, &srcrect);
}

void HookAnimationComponent::renderHookChains()
{
	Uint32 ticks = SDL_GetTicks();
	MainCharacter* mc = PlayState::getInstance()->getMainCharacter();

	Vector2D hookSize = hook->getCenterPos() - mc->getCenterPos();
	float hookLength = hookSize.magnitude();
	
	Uint32 sprite = (ticks / fps) % hookChainTex->getNumCols();
	SDL_Rect srcrect = { sprite * hookChainTex->getFrameWidth(), animationNumber * hookChainTex->getFrameHeight(), hookLength, hookChainTex->getFrameHeight() };
	SDL_Rect dstrect = { mc->getDisplayCenterPos().getX(), mc->getDisplayCenterPos().getY() - srcrect.h/2 , srcrect.w*Game::getGame()->getScale()/3, srcrect.h*Game::getGame()->getScale() / 3 };
	

	angle = getSpriteAngle();


	SDL_Point center;
	center.x = 0;
	center.y = dstrect.h / 2;

	hookChainTex->render(dstrect, angle, &center, &srcrect);
}

void HookAnimationComponent::renderHookFail()
{

	Uint32 ticks = SDL_GetTicks();
	MainCharacter* mc = PlayState::getInstance()->getMainCharacter();

	Vector2D hookSize = hook->getCenterPos() - mc->getCenterPos();
	float hookLength = hookSize.magnitude();
	
	hookFailAnim->update();
	if (hookFailAnim->TimeSinceTimerCreation*1000>50) {
		hookFailSprite++;
		hookFailAnim->restart();
	}
	if (hookFailSprite >= hookChainFailTex->getNumCols()) {
		Message msg(HOOK_STOP);
		mc->sendMessage(&msg);
		hookFailSprite = hookChainFailTex->getNumCols()-1;
		hookFailAnim->restart();
	}

	SDL_Rect srcrect = { hookFailSprite * hookChainFailTex->getFrameWidth(), animationNumber * hookChainFailTex->getFrameHeight(),hookChainFailTex->getFrameWidth(), hookChainFailTex->getFrameHeight() };
	SDL_Rect dstrect = { mc->getDisplayCenterPos().getX(), mc->getDisplayCenterPos().getY() - srcrect.h / 2 , srcrect.w*Game::getGame()->getScale() / 3, srcrect.h*Game::getGame()->getScale() / 3 };
	
	angle = getSpriteAngle();

	SDL_Point center;
	center.x = 0;
	center.y = dstrect.h / 2;

	hookChainFailTex->render(dstrect, angle, &center, &srcrect);
}

void HookAnimationComponent::setAngle(float angle)
{
	this->angle = angle;
}

void HookAnimationComponent::setFlip(SDL_RendererFlip flip)
{
	this->flip = flip;
}

float HookAnimationComponent::getSpriteAngle()
{

	MainCharacter* mc = PlayState::getInstance()->getMainCharacter();

	angle = hook->getAngle();
	Vector2D displayPosition;//Posición del personaje relativa a la cámara
	displayPosition = hook->getDisplayCenterPos();
	Vector2D mcDisplayPos = mc->getDisplayCenterPos();


	float angle = (atan2(displayPosition.getY() - mcDisplayPos.getY(), displayPosition.getX() - mcDisplayPos.getX()));//Angulo entre el cursor y el jugador, en grados

	angle = angle * 180 / M_PI;
	if (angle < 0)
		angle += 360;
	
	return angle;
}

HookAnimationComponent::~HookAnimationComponent()
{
}
