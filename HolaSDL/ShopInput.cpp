#include "ShopInput.h"
#include "PlayState.h"
#include "CollisionHandler.h"

ShopInput::ShopInput(GameObject * o) : InputComponent(o)
{
}

ShopInput::~ShopInput()
{
}

void ShopInput::handleEvents(SDL_Event & e)
{
	//Si el jugador esta dentro de nosotros ;) y pulsa la e, empezamos la secuencia	
	if (CollisionHandler::RectCollide(gameObject->getTransform()->body, PlayState::getInstance()->getMainCharacter()->getTransform()->body)) {
			if (e.key.keysym.sym == SDLK_e)
			{
				PlayState::getInstance()->openShop();
			}
	}
}
