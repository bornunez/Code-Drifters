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
		else if(hook->getHookStatus() != HookStatus::FAIL){
			renderHookFail();
		}
	}

}

void HookAnimationComponent::renderHookHead()
{
	MainCharacter* mc = PlayState::getInstance()->getMainCharacter();

	Uint32 ticks = SDL_GetTicks();

	float displayX = hook->getDisplayCenterPos().getX();
	float displayY = hook->getDisplayCenterPos().getY();

	Uint32 sprite = (ticks / fps) % hookHeadTex->getNumCols();
	SDL_Rect srcrect = { sprite * hookHeadTex->getFrameWidth(), animationNumber * hookHeadTex->getFrameHeight(), hookHeadTex->getFrameWidth(), hookHeadTex->getFrameHeight() };
	SDL_Rect dstrect = { displayX - hook->getTransform()->body.w / 2, displayY - hook->getTransform()->body.h / 2, hook->getTransform()->body.w*Game::getGame()->getScale()/3,  hook->getTransform()->body.h*Game::getGame()->getScale()/3};

	angle = getSpriteAngle(mc->getGunPosition(), hook->getDisplayCenterPos());

	SDL_Point center;
	center.x = dstrect.w / 2;
	center.y = dstrect.h / 2;

	hookHeadTex->render(dstrect, angle, &center, &srcrect);
}

void HookAnimationComponent::renderHookChains()
{
	Uint32 ticks = SDL_GetTicks();
	MainCharacter* mc = PlayState::getInstance()->getMainCharacter();
	Vector2D originPos;//Posici�n de la que sale el gancho
	Vector2D originDisplayPos;//La misma posici�n pero relativa a la c�mara

	if (mc->getMCState() == MCState::Dash) {
		originPos = mc->getCenterPos();
		originDisplayPos = mc->getDisplayCenterPos();
	}
	else {
		originPos = mc->getGunPosition() + PlayState::getInstance()->getCamera()->getTransform()->position;
		originDisplayPos = mc->getGunPosition();
	}


	Vector2D hookSize = originPos - hook->getCenterPos();//Calcula el tama�o que debe tener el gancho restando el origen al destino
	float hookLength = hookSize.magnitude();
	
	Uint32 sprite = (ticks / fps) % hookChainTex->getNumCols();
	SDL_Rect srcrect = { sprite * hookChainTex->getFrameWidth(), animationNumber * hookChainTex->getFrameHeight(), hookLength, hookChainTex->getFrameHeight() };
	SDL_Rect dstrect = { originDisplayPos.getX() , originDisplayPos.getY() - srcrect.h/2 , srcrect.w*Game::getGame()->getScale()/3, srcrect.h*Game::getGame()->getScale() / 3 };
	
	Vector2D displayHookPosition;//Posici�n del gancho relativa a la c�mara
	displayHookPosition = hook->getDisplayCenterPos();
	

	angle = getSpriteAngle(originDisplayPos, displayHookPosition);//Calcula el �ngulo entre el origen del gancho y el gancho en s�

	SDL_Point center;
	center.x = 0;
	center.y = dstrect.h / 2;

	hookChainTex->render(dstrect, angle, &center, &srcrect);
}

void HookAnimationComponent::renderHookFail()
{

	Uint32 ticks = SDL_GetTicks();
	MainCharacter* mc = PlayState::getInstance()->getMainCharacter();

	Vector2D gunPos = mc->getGunPosition() + PlayState::getInstance()->getCamera()->getTransform()->position;
	Vector2D hookSize = hook->getCenterPos() - mc->getDisplayCenterPos();
	float hookLength = hookSize.magnitude();

	hookFailAnim->update();//Contador del tiempo que est� activo el gancho fail
	if (hookFailAnim->TimeSinceTimerCreation*1000>40) {
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
	
	

	angle = hook->getAngle();
	Vector2D hookDisplayPosition;//Posici�n delgancho relativa a la c�mara
	hookDisplayPosition = hook->getDisplayCenterPos();
	Vector2D mcDisplayPos = mc->getDisplayCenterPos();

	angle = getSpriteAngle(mcDisplayPos, hookDisplayPosition);

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
float HookAnimationComponent::getSpriteAngle(Vector2D origin, Vector2D target)
{

	MainCharacter* mc = PlayState::getInstance()->getMainCharacter();

	angle = hook->getAngle();
	Vector2D displayPosition;//Posici�n del personaje relativa a la c�mara
	displayPosition = hook->getDisplayCenterPos();
	Vector2D mcDisplayPos = mc->getGunPosition();


	float angle = (atan2(target.getY() - origin.getY(), target.getX() - origin.getX()));//Angulo entre el cursor y el jugador, en grados

	angle = angle * 180 / M_PI;
	if (angle < 0)
		angle += 360;

	return angle;
}

HookAnimationComponent::~HookAnimationComponent()
{
}
