#include "HealInput.h"
#include "PlayState.h"
#include "CollisionHandler.h"
#include "MainCharacter.h"

HealInput::HealInput(GameObject * o) : InputComponent(o)
{
}

HealInput::~HealInput()
{
}

void HealInput::handleEvents(SDL_Event & e)
{
	mc = PlayState::getInstance()->getMainCharacter();
	//Si el jugador esta dentro de nosotros ;) y pulsa la e, empezamos la secuencia	
	if (CollisionHandler::RectCollide(gameObject->getTransform()->body, mc->getTransform()->body)) {
		if (e.key.keysym.sym == SDLK_e)
		{
			if (mc->getMoney() >= 10) {
				mc->changeMoney(-10);
				mc->addHP(25);
			}
		}
	}
}
