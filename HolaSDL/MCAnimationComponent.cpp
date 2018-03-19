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
void MCAnimationComponent::recieveMessage(std::string msg) {
		if (msg == "ATTACK1_LEFT") {//En las animaciones de ataque, estas se reinician para empezar en el frame 0
			gameObject->changeCurrentAnimation("ATTACK1_LEFT");
			gameObject->getCurrentAnimation()->startAnimation();
		}
		else if (msg == "ATTACK2_LEFT") {
			gameObject->changeCurrentAnimation("ATTACK2_LEFT");
			gameObject->getCurrentAnimation()->startAnimation();
		}
		else if (msg == "ATTACK3_LEFT") {
			gameObject->changeCurrentAnimation("ATTACK3_LEFT");
			gameObject->getCurrentAnimation()->startAnimation();
		}
		else if (msg == "ATTACK1_RIGHT") {
			gameObject->changeCurrentAnimation("ATTACK1_RIGHT");
			gameObject->getCurrentAnimation()->startAnimation();
		}
		else if (msg == "ATTACK2_RIGHT") {
			gameObject->changeCurrentAnimation("ATTACK2_RIGHT");
			gameObject->getCurrentAnimation()->startAnimation();
		}
		else if (msg == "ATTACK3_RIGHT") {
			gameObject->changeCurrentAnimation("ATTACK3_RIGHT");
			gameObject->getCurrentAnimation()->startAnimation();
		}
		else if (msg == "ATTACK1_TOPLEFT") {//En las animaciones de ataque, estas se reinician para empezar en el frame 0
			gameObject->changeCurrentAnimation("ATTACK1_TOPLEFT");
			gameObject->getCurrentAnimation()->startAnimation();
		}
		else if (msg == "ATTACK2_TOPLEFT") {
			gameObject->changeCurrentAnimation("ATTACK2_TOPLEFT");
			gameObject->getCurrentAnimation()->startAnimation();
		}
		else if (msg == "ATTACK3_TOPLEFT") {
			gameObject->changeCurrentAnimation("ATTACK3_TOPLEFT");
			gameObject->getCurrentAnimation()->startAnimation();
		}
		else if (msg == "ATTACK1_TOPRIGHT") {
			gameObject->changeCurrentAnimation("ATTACK1_TOPRIGHT");
			gameObject->getCurrentAnimation()->startAnimation();
		}
		else if (msg == "ATTACK2_TOPRIGHT") {
			gameObject->changeCurrentAnimation("ATTACK2_TOPRIGHT");
			gameObject->getCurrentAnimation()->startAnimation();
		}
		else if (msg == "ATTACK3_TOPRIGHT") {
			gameObject->changeCurrentAnimation("ATTACK3_TOPRIGHT");
			gameObject->getCurrentAnimation()->startAnimation();
		}
		else if (msg == "ATTACK1_BOTLEFT") {//En las animaciones de ataque, estas se reinician para empezar en el frame 0
			gameObject->changeCurrentAnimation("ATTACK1_BOTLEFT");
			gameObject->getCurrentAnimation()->startAnimation();
		}
		else if (msg == "ATTACK2_BOTLEFT") {
			gameObject->changeCurrentAnimation("ATTACK2_BOTLEFT");
			gameObject->getCurrentAnimation()->startAnimation();
		}
		else if (msg == "ATTACK3_BOTLEFT") {
			gameObject->changeCurrentAnimation("ATTACK3_BOTLEFT");
			gameObject->getCurrentAnimation()->startAnimation();
		}
		else if (msg == "ATTACK1_BOTRIGHT") {
			gameObject->changeCurrentAnimation("ATTACK1_BOTRIGHT");
			gameObject->getCurrentAnimation()->startAnimation();
		}
		else if (msg == "ATTACK2_BOTRIGHT") {
			gameObject->changeCurrentAnimation("ATTACK2_BOTRIGHT");
			gameObject->getCurrentAnimation()->startAnimation();
		}
		else if (msg == "ATTACK3_BOTRIGHT") {
			gameObject->changeCurrentAnimation("ATTACK3_BOTRIGHT");
			gameObject->getCurrentAnimation()->startAnimation();
		}
	else if (msg == "RUN_LEFT") {
		gameObject->changeCurrentAnimation("RUN_LEFT");
	}
	else if (msg == "RUN_RIGHT") {
		gameObject->changeCurrentAnimation("RUN_RIGHT");
	}
	else if (msg == "RUN_TOP") {
		gameObject->changeCurrentAnimation("RUN_TOP");
	}
	else if (msg == "RUN_BOT") {
		gameObject->changeCurrentAnimation("RUN_BOT");
	}
	else if (msg == "IDLE_LEFT") {
		gameObject->changeCurrentAnimation("IDLE_LEFT");
	}
	else if (msg == "IDLE_RIGHT") {
		gameObject->changeCurrentAnimation("IDLE_RIGHT");
	}
	else if (msg == "IDLE_TOP") {
		gameObject->changeCurrentAnimation("IDLE_TOP");
	}
	else if (msg == "IDLE_BOT") {
		gameObject->changeCurrentAnimation("IDLE_BOT");
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
	if (gameObject->getCurrentAnimation()->isFinished() || mc->getActionState() == Idle) {
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
	if (mc->getActionState() == Run) {
		Vector2D direction = gameObject->getTransform()->direction;
		
		if (direction.getX() == 0 && direction.getY() == 1) {//Abajo

			gameObject->sendMessage("RUN_BOT");
		}
		else if (direction.getX() == 0 && direction.getY() == -1) {//Arriba

			gameObject->sendMessage("RUN_TOP");
		}
		else if (direction.getX() == 1) {//Derecha

			gameObject->sendMessage("RUN_RIGHT");
		}
		else if (direction.getX() == -1) {//Izquierda

			gameObject->sendMessage("RUN_LEFT");
		}
	}
}
