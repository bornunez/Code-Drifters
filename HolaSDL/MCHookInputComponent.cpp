#include "MCHookInputComponent.h"
#include "GameObject.h"
#include "MainCharacter.h"
#include "PlayState.h"
#include "Camera.h"
#include "Hook.h"
MCHookInputComponent::MCHookInputComponent(MainCharacter * mc) : InputComponent(static_cast<GameObject*>(mc))
{
	this->mc = mc;
}


MCHookInputComponent::~MCHookInputComponent()
{
}

void MCHookInputComponent::handleEvents(SDL_Event & e)
{
	if (static_cast<MainCharacter*>(gameObject)->getActionState() != Hooking) {
		if (e.key.keysym.sym == SDLK_SPACE && e.type == SDL_KEYDOWN) {
			int mouseX, mouseY;
			SDL_Point p;
			SDL_Rect r;
			SDL_GetMouseState(&p.x, &p.y);
			cursorPos.setX(p.x);
			cursorPos.setY(p.y);//Posición del cursor en pantalla

						  //Cambia la posición de donde sala la bala, es temporal hasta que tengamos los frames de la animación definidos
			Vector2D gunPosition;
			gunPosition.setX(getGameObject()->getTransform()->position.getX() + getGameObject()->getTransform()->body.w / 2);
			gunPosition.setY(getGameObject()->getTransform()->position.getY() + getGameObject()->getTransform()->body.h / 2);
			mc->setGunPosition(gunPosition);

			Vector2D displayPosition;//Posición del personaje relativa a la cámara
			displayPosition = (gunPosition
				- PlayState::getInstance()->getCamera()->getTransform()->position);

			Vector2D hookDirection;
			hookDirection = cursorPos - displayPosition;
			hookDirection.normalize();

			mc->shootHook(gunPosition, hookDirection);

		}
	}

}
