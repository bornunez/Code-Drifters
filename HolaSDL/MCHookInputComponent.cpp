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
	if (mc->getMCState() != MCState::Dash) {
		if (e.key.keysym.sym == SDLK_SPACE && e.type == SDL_KEYDOWN) {
			if ((mc->getMCState() == MCState::Idle || mc->getMCState() == MCState::Run || mc->getMCState() == MCState::DashEnd) && !mc->getHook().isActive()) {
				int mouseX, mouseY;
				SDL_Point p;
				SDL_Rect r;
				SDL_GetMouseState(&p.x, &p.y);
				cursorPos.setX(p.x);
				cursorPos.setY(p.y);//Posición del cursor en pantalla

				//Cambia la posición de donde sala el gancho,  HAY QUE CAMBIARLO PARA QUE SALGA DEL GUNPOSITION BUENO
				Vector2D gunDisplayPosition;
				gunDisplayPosition = mc->getGunPosition();

				Vector2D gunPosition = mc->getGunPosition() + PlayState::getInstance()->getCamera()->getTransform()->position;

				Vector2D targetPosition;//Es la posición donde llega el gancho, se tiene en cuenta que el centro del gancho debe llegar al punto justo del cursor
				targetPosition = cursorPos;
				targetPosition.setX(targetPosition.getX()-mc->getHook().getTransform()->body.w/2);
				targetPosition.setY(targetPosition.getY() - mc->getHook().getTransform()->body.h / 2);

				Vector2D hookDirection;
				hookDirection = targetPosition - gunDisplayPosition ;
				hookDirection.normalize();

				float angle = (atan2(hookDirection.getY(), hookDirection.getX()));
				angle = angle * 180 / M_PI;
				if (angle < 0)
					angle += 360;

				if (angle < 315 && angle >= 225) {
					mc->getTransform()->direction.set(0, -1);
				}
				else if (angle <225 && angle >= 135) {
					mc->getTransform()->direction.set(-1, 0);
				}
				else if (angle <135 && angle >= 45) {
					mc->getTransform()->direction.set(0, 1);
				}
				else {
					mc->getTransform()->direction.set(1, 0);
				}
				

				mc->shootHook(gunPosition, hookDirection);
			}
		}
	}

}
