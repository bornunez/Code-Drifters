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
		if (!flag && e.key.keysym.sym == SDLK_e)
		{
			if (mc->getMoney() >= 10) {
				mc->changeMoney(-10);
				mc->addHP(25);
			}
			flag = true;
		}
		if (flag && e.type == SDL_KEYUP) {
			if (e.key.keysym.sym == SDLK_e)
			{
				flag = false;
			}
		}
	}
	else
		flag = false;
}
