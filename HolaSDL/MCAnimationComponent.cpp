#include "MCAnimationComponent.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"
#include "MainCharacter.h"
#include "ResourceManager.h"
#include "ParticlesManager.h"
#include "Hook.h"
MCAnimationComponent::MCAnimationComponent(MainCharacter* o, std::map<const char*, Animation*> anim) : RenderComponent(static_cast<GameObject*>(o))
{
	mc = o;
	animations = anim;
	gameObject->changeCurrentAnimation("IDLE_BOT");
	gunTexture = ResourceManager::getInstance()->getTexture(MCGun);
	gunTimer = new Timer();
	hurtTimer = new Timer();
}


MCAnimationComponent::~MCAnimationComponent()
{
}

void MCAnimationComponent::receiveMessage(Message* msg) {

	switch (msg->id) {
	case ATTACK1_LEFT:
		gameObject->changeCurrentAnimation("ATTACK1_LEFT");	//En las animaciones de ataque, estas se reinician para empezar en el frame 0
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case ATTACK2_LEFT:
		gameObject->changeCurrentAnimation("ATTACK2_LEFT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case ATTACK3_LEFT:
		gameObject->changeCurrentAnimation("ATTACK3_LEFT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case ATTACK1_RIGHT:
		gameObject->changeCurrentAnimation("ATTACK1_RIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case ATTACK2_RIGHT:
		gameObject->changeCurrentAnimation("ATTACK2_RIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case ATTACK3_RIGHT:
		gameObject->changeCurrentAnimation("ATTACK3_RIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case ATTACK1_TOPLEFT:
		gameObject->changeCurrentAnimation("ATTACK1_TOPLEFT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case ATTACK2_TOPLEFT:
		gameObject->changeCurrentAnimation("ATTACK2_TOPLEFT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case ATTACK3_TOPLEFT:
		gameObject->changeCurrentAnimation("ATTACK3_TOPLEFT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case ATTACK1_TOPRIGHT:
		gameObject->changeCurrentAnimation("ATTACK1_TOPRIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case ATTACK2_TOPRIGHT:
		gameObject->changeCurrentAnimation("ATTACK2_TOPRIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case ATTACK3_TOPRIGHT:
		gameObject->changeCurrentAnimation("ATTACK3_TOPRIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case ATTACK1_BOTLEFT:
		gameObject->changeCurrentAnimation("ATTACK1_BOTLEFT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case ATTACK2_BOTLEFT:
		gameObject->changeCurrentAnimation("ATTACK2_BOTLEFT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case ATTACK3_BOTLEFT:
		gameObject->changeCurrentAnimation("ATTACK3_BOTLEFT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case ATTACK1_BOTRIGHT:
		gameObject->changeCurrentAnimation("ATTACK1_BOTRIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case ATTACK2_BOTRIGHT:
		gameObject->changeCurrentAnimation("ATTACK2_BOTRIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case ATTACK3_BOTRIGHT:
		gameObject->changeCurrentAnimation("ATTACK3_BOTRIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
		break;
	case RUN_LEFT:
		gameObject->changeCurrentAnimation("RUN_LEFT");
		break;
	case RUN_RIGHT:
		gameObject->changeCurrentAnimation("RUN_RIGHT");
		break;
	case RUN_TOP:
		gameObject->changeCurrentAnimation("RUN_TOP");
		break;
	case RUN_BOT:
		gameObject->changeCurrentAnimation("RUN_BOT");
		break;
	case IDLE_LEFT:
		gameObject->changeCurrentAnimation("IDLE_LEFT");
		break;
	case IDLE_RIGHT:
		gameObject->changeCurrentAnimation("IDLE_RIGHT");
		break;
	case IDLE_TOP:
		gameObject->changeCurrentAnimation("IDLE_TOP");
		break;
	case IDLE_BOT:
		gameObject->changeCurrentAnimation("IDLE_BOT");
		break;
	case HOOK_WALL:
		//mc->setMCState(MCState::Dash);
		handleAnimationDash();
		break;
	case HOOK_ENEMY:
		handleAnimationShot();
		break;
	case HOOK_EXTEND:
		handleAnimationShot();
		break;
	case HOOK_FAIL:
		break;
	case HOOK_EMPTY:
		break;
	case HOOK_STOP:
		handleAnimationEndDash();
		break;
	case MC_SHOT:
		gunTimer->restart();
		//mc->setMCState(MCState::Shot);
		break;
	case MC_HOOKSHOT:
		//mc->setMCState(MCState::HookShot);
		break;
	case ENEMY_BULLET_COLLISION:
		handleAnimationHurt();
		break;
	case STALKER_ATTACK:
		handleAnimationHurt();
		break;
	case MC_DEATH:
		handleAnimationDeath();
		break;
	}
}

void MCAnimationComponent::render()//Renderiza la animación actual, (siempre tiene que haber asignada una animación para que se vea en pantalla)
{
	if (mc->getMCState() == MCState::Shot || mc->getMCState() == MCState::HookShot) {//Cuando está disparando aparece la pistola
		
		float angle = handleGunAngle();
		if (angle > 135 && angle < 315) {//Arriba a la izquierda la pistola se ve detrás
			handleAnimationGun();
			gameObject->getCurrentAnimation()->runAnimation();
		}
		else {
			gameObject->getCurrentAnimation()->runAnimation();
			handleAnimationGun();
		}
		gunTimer->update();
		if (gunTimer->TimeSinceTimerCreation > 0.5) {
			gunTimer->restart();
			mc->setMCState(MCState::Idle);
		}
	}
	else {
		handleAnimationStates();
		gameObject->getCurrentAnimation()->runAnimation();
	}
	

}


void MCAnimationComponent::handleAnimationStates()
{
	//IDLE POSITIONS
	if (mc->getMCState() == MCState::Hurt) {
		hurtTimer->update();
		if (hurtTimer->TimeSinceTimerCreation > hurtTime) {
			mc->setMCState(MCState::Idle);
			gameObject->changeCurrentAnimation("RUN");
		}
	}

	if (mc->getMCState() == MCState::Attack && gameObject->getCurrentAnimation()->isFinished()) {
		mc->setMCState(MCState::Idle);
	}
	else if (mc->getMCState() == MCState::DashEnd && gameObject->getCurrentAnimation()->isFinished()) {
		mc->setMCState(MCState::Idle);
	}
	if (mc->getMCState() == MCState::Idle) {
		Vector2D direction = gameObject->getTransform()->direction;
		if (direction.getX() == 1 && direction.getY() == 0) {//Derecha
			gameObject->changeCurrentAnimation("IDLE_RIGHT");
		}
		else if (direction.getX() == -1 && direction.getY() == 0) {//Izquierda
			gameObject->changeCurrentAnimation("IDLE_LEFT");
		}
		else if (direction.getX() == 0 && direction.getY() == 1) {//Abajo
			gameObject->changeCurrentAnimation("IDLE_BOT");
		}
		else if (direction.getX() == 0 && direction.getY() == -1) {//Arriba
			gameObject->changeCurrentAnimation("IDLE_TOP");
		}
		else {
			gameObject->changeCurrentAnimation("IDLE_BOT");
		}
	}
	//RUN POSITIONS
	if (mc->getMCState() == MCState::Run) {

		Message msg(NO_ID);

		Vector2D direction = gameObject->getTransform()->direction;
		
		if (direction.getX() == 0 && direction.getY() == 1) {//Abajo
			msg.id = RUN_BOT;
		}
		else if (direction.getX() == 0 && direction.getY() == -1) {//Arriba
			msg.id = RUN_TOP;
		}
		else if (direction.getX() == 1) {//Derecha
			msg.id = RUN_RIGHT;
		}
		else if (direction.getX() == -1) {//Izquierda
			msg.id = RUN_LEFT;
		}
		//Envia el mensaje
		gameObject->sendMessage(&msg);
	}
	
}

void MCAnimationComponent::handleAnimationHook()
{
	
}

void MCAnimationComponent::handleAnimationShot()
{
}

void MCAnimationComponent::handleAnimationDash()
{
	//HOOK STATE
	//if (mc->getMCState() == MCState::Dash) {
		Vector2D direction = gameObject->getTransform()->direction;
		if (direction.getX() == 1 && direction.getY() == 0) {//Derecha
			gameObject->changeCurrentAnimation("DASH_RIGHT");
		}
		else if (direction.getX() == -1 && direction.getY() == 0) {//Izquierda
			gameObject->changeCurrentAnimation("DASH_LEFT");
		}
		else if (direction.getX() == 0 && direction.getY() == 1) {//Abajo
			gameObject->changeCurrentAnimation("DASH_BOT");
		}
		else if (direction.getX() == 0 && direction.getY() == -1) {//Arriba
			gameObject->changeCurrentAnimation("DASH_TOP");
		}
	//}
}

void MCAnimationComponent::handleAnimationEndDash()
{
	//HOOK STATE
	Vector2D direction = gameObject->getTransform()->direction;
	if (direction.getX() == 1 && direction.getY() == 0) {//Derecha
		gameObject->changeCurrentAnimation("DASHEND_RIGHT");
		gameObject->getCurrentAnimation()->startAnimation();
	}
	else if (direction.getX() == -1 && direction.getY() == 0) {//Izquierda
		gameObject->changeCurrentAnimation("DASHEND_LEFT");
		gameObject->getCurrentAnimation()->startAnimation();
	}
	else if (direction.getX() == 0 && direction.getY() == 1) {//Abajo
		gameObject->changeCurrentAnimation("DASHEND_BOT");
		gameObject->getCurrentAnimation()->startAnimation();
	}
	else if (direction.getX() == 0 && direction.getY() == -1) {//Arriba
		gameObject->changeCurrentAnimation("DASHEND_TOP");
		gameObject->getCurrentAnimation()->startAnimation();
	}
//	mc->setMCState(MCState::DashEnd);
//	mc->setMovable(true);	
}

//Cambia la animacion a HURT y crea una particula de sangre
void MCAnimationComponent::handleAnimationHurt()
{
	//cout << mc->getActualHP();
	gameObject->changeCurrentAnimation("HURT");
	//mc->setMCState(MCState::Hurt);
	hurtTimer->restart();
	//ParticlesManager::getInstance()->getParticle(ParticleType::Blood, mc->getCenterPos().getX(), mc->getCenterPos().getY());
}

void MCAnimationComponent::handleAnimationDeath()
{
	gameObject->changeCurrentAnimation("DEATH");
}

void MCAnimationComponent::handleAnimationGun()
{
	Uint32 ticks = SDL_GetTicks();


	float angle = handleGunAngle();

	if (angle > 45 && angle < 135) {//Abajo
		gameObject->changeCurrentAnimation("SHOT_BOT");
	}
	else if (angle >= 135 && angle<225) {//Izquierda
		gameObject->changeCurrentAnimation("SHOT_LEFT");
	}
	else if (angle >= 225 && angle<315) {//Arriba
		gameObject->changeCurrentAnimation("SHOT_TOP");
	}
	else {//Derecha
		gameObject->changeCurrentAnimation("SHOT_RIGHT");
	}
	gameObject->getCurrentAnimation()->startAnimation();

	float displayX = mc->getDisplayCenterPos().getX();
	float displayY = mc->getDisplayCenterPos().getY();
	float spritePosX = displayX - gunTexture->getFrameWidth()*Game::getGame()->getScale() / 2;
	float spritePosY = displayY - gunTexture->getFrameHeight()*Game::getGame()->getScale() / 2;
	float spriteW = gunTexture->getFrameWidth()*Game::getGame()->getScale();
	float spriteH = gunTexture->getFrameHeight()*Game::getGame()->getScale();
	float offsetX = 0;
	float offsetY = 0;

	if (angle > 45 && angle < 135) {//Abajo
		if (angle > 90) {//Abajo a la izquierda
			offsetY += 2;
			offsetX -= 2;
		}
		else {//Abajo a la derecha
			offsetY += 2;
			offsetX -= 6;
		}
		
	}
	else if(angle>=135 && angle<225) {//Izquierda
		 offsetX += 1;
	}
	else if (angle >= 225 && angle<315) {//Arriba
		if (angle>270) {//Arriba a la derecha
			offsetY -= 2;
			offsetX += 5;
		}
		else {
			offsetY -= 2;
			offsetX += 2;
		}
	}
	else {//Derecha
		offsetY += 2;
		offsetX += 2;
	}
	offsetY *= Game::getGame()->getScale();
	offsetX *= Game::getGame()->getScale();

	SDL_RendererFlip flip;
	if (angle >= 90 && angle<270) {
		flip = SDL_FLIP_HORIZONTAL;
		angle -= 180;
	}
	else {
		flip = SDL_FLIP_NONE;
	}
	SDL_Rect srcrect = { 0, 0, gunTexture->getFrameWidth(), gunTexture->getFrameHeight() };
	SDL_Rect dstrect = { spritePosX + offsetX, spritePosY + offsetY,spriteW, spriteH };

	SDL_Point center;
	center.x = dstrect.w / 2;
	center.y = dstrect.h / 2;

	gunTexture->render(dstrect, angle, &center, &srcrect, flip);
}

float MCAnimationComponent::handleGunAngle()
{
	float gunAngle;
	int targetX, targetY;

	if (mc->getMCState() == MCState::Shot) {
		SDL_Point p;//El target aquí es el cursor
		SDL_GetMouseState(&p.x, &p.y);
		targetX = p.x;
		targetY = p.y;

	}
	else if (mc->getMCState() == MCState::HookShot) {

		targetX = mc->getHook().getDisplayCenterPos().getX();
		targetY = mc->getHook().getDisplayCenterPos().getY();
	}

	Vector2D mcDisplayPos = mc->getDisplayCenterPos();


	gunAngle = (atan2(targetY - mcDisplayPos.getY(), targetX - mcDisplayPos.getX()));//Angulo entre el cursor y el jugador, en grados

	gunAngle = gunAngle * 180 / M_PI;
	if (gunAngle < 0)
		gunAngle += 360;

	return gunAngle;
}

