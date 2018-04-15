#include "MCAnimationComponent.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"
#include "MainCharacter.h"
MCAnimationComponent::MCAnimationComponent(GameObject* o, std::map<const char*, Animation*> anim) : RenderComponent(o)
{
	animations = anim;
	gameObject->changeCurrentAnimation("IDLE_BOT");
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
	case ENEMY_BULLET_COLLISION:
		handleAnimationHurt();
		break;
	}
}

void MCAnimationComponent::render()//Renderiza la animación actual, (siempre tiene que haber asignada una animación para que se vea en pantalla)
{
	handleAnimationStates();
	gameObject->getCurrentAnimation()->runAnimation();

}


void MCAnimationComponent::handleAnimationStates()
{
	
	//IDLE POSITIONS
	MainCharacter* mc = static_cast<MainCharacter*>(gameObject);
	cout << mc->getMCState();
	if ((gameObject->getCurrentAnimation()->isFinished() || mc->getMCState() == MCState::Idle)) {
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
	MainCharacter* mc = static_cast<MainCharacter*>(gameObject);
	//HOOK STATE
	if (mc->getMCState() == MCState::Hooking) {
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
	}
}

void MCAnimationComponent::handleAnimationEndDash()
{
	MainCharacter* mc = static_cast<MainCharacter*>(gameObject);
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
	mc->setMCState(MCState::DashEnd);
	mc->setMovable(true);	
}

//Cambia la animacion a HURT y crea una particula de sangre
void MCAnimationComponent::handleAnimationHurt()
{
	gameObject->changeCurrentAnimation("HURT");
	static_cast<MainCharacter*>(gameObject)->setMCState(MCState::Hurt);
}

