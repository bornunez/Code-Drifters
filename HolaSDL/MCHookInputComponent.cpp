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
	if (static_cast<MainCharacter*>(gameObject)->getMCState() != MCState::Hooking) {
		if (e.key.keysym.sym == SDLK_SPACE && e.type == SDL_KEYDOWN) {
			if (static_cast<MainCharacter*>(gameObject)->getMCState() != MCState::Attack) {
				int mouseX, mouseY;
				SDL_Point p;
				SDL_Rect r;
				SDL_GetMouseState(&p.x, &p.y);
				cursorPos.setX(p.x);
				cursorPos.setY(p.y);//Posición del cursor en pantalla

				//Cambia la posición de donde sala el gancho,  HAY QUE CAMBIARLO PARA QUE SALGA DEL GUNPOSITION BUENO
				Vector2D gunPosition;
				gunPosition = mc->getCenterPos();

				Vector2D displayPosition = mc->getDisplayCenterPos();

				Vector2D targetPosition;//Es la posición donde llega el gancho, se tiene en cuenta que el centro del gancho debe llegar al punto justo del cursor
				targetPosition = cursorPos;
				targetPosition.setX(targetPosition.getX()-mc->getHook().getTransform()->body.w/2);
				targetPosition.setY(targetPosition.getY() - mc->getHook().getTransform()->body.h / 2);

				Vector2D hookDirection;
				hookDirection = targetPosition - displayPosition;
				hookDirection.normalize();
				

				mc->shootHook(gunPosition, hookDirection);
			}
		}
	}

}
