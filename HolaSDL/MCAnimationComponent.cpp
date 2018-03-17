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

	if (msg == "RUN_LEFT") {
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
	else if (msg == "ATTACK1_LEFT") {//En las animaciones de ataque, estas se reinician para empezar en el frame 0
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
}
void MCAnimationComponent::render()//Renderiza la animación actual, (siempre tiene que haber asignada una animación para que se vea en pantalla)
{
	handleAnimationStates();
	gameObject->getCurrentAnimation()->runAnimation();
	debugBoxes();
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
		if (direction.getX() == 1 && direction.getY() == 0) {//Derecha

			gameObject->sendMessage("RUN_RIGHT");
		}
		else if (direction.getX() == -1 && direction.getY() == 0) {//Izquierda

			gameObject->sendMessage("RUN_LEFT");
		}
		else if (direction.getX() == 0 && direction.getY() == 1) {//Abajo

			gameObject->sendMessage("RUN_BOT");
		}
		else if (direction.getX() == 0 && direction.getY() == -1) {//Arriba

			gameObject->sendMessage("RUN_TOP");
		}
	}
}
