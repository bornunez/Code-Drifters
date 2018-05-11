#include "PressToInteract.h"
#include "PlayState.h"
#include "CollisionHandler.h"



PressToInteract::PressToInteract(GameObject* o) : RenderComponent(o)
{
}


PressToInteract::~PressToInteract()
{
}

void PressToInteract::lateRender()
{
	if (CollisionHandler::RectCollide(gameObject->getTransform()->body, PlayState::getInstance()->getMainCharacter()->getTransform()->body)) {
		std::cout << "PULSA E PARA ENTRAR A LA TIENDA"<<endl;
	}
}
