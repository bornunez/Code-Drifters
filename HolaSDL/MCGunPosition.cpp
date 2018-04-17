#include "MCGunPosition.h"
#include "MainCharacter.h"
#include "Game.h"

MCGunPosition::MCGunPosition(MainCharacter* mc ) : UpdateComponent(static_cast<GameObject*>(mc))
{
	this->mc = mc;
}


MCGunPosition::~MCGunPosition()
{
}

void MCGunPosition::update()
{
	handleGunAngle();
}

float MCGunPosition::handleGunAngle()
{
	float gunAngle=0;
	int targetX=0, targetY=0;

	if (mc->getMCState() == MCState::HookShot) {

		targetX = mc->getHook().getDisplayCenterPos().getX();
		targetY = mc->getHook().getDisplayCenterPos().getY();
	}
	else {
		SDL_Point p;//El target aquí es el cursor
		SDL_GetMouseState(&p.x, &p.y);
		targetX = p.x;
		targetY = p.y;
	}

	Vector2D mcDisplayPos = mc->getDisplayCenterPos();


	gunAngle = (atan2(targetY - mcDisplayPos.getY(), targetX - mcDisplayPos.getX()));//Angulo entre el cursor y el jugador, en grados

	gunAngle = gunAngle * 180 / M_PI;
	if (gunAngle < 0)
		gunAngle += 360;

	Vector2D gunDirection;
	gunDirection.setX(targetX - mcDisplayPos.getX());
	gunDirection.setY(targetY - mcDisplayPos.getY());
	gunDirection.normalize();

	float offsetX = 0;
	float offsetY = 0;

	if (gunAngle > 45 && gunAngle < 135) {//Abajo
		if (gunAngle > 90) {//Abajo a la izquierda
			offsetY += 4;
			offsetX -= 7;
		}
		else {//Abajo a la derecha
			offsetY += 1;
			offsetX -= 1;
		}

	}
	else if (gunAngle >= 135 && gunAngle<225) {//Izquierda
		offsetX += 1;
		offsetY -= 5;
	}
	else if (gunAngle >= 225 && gunAngle<315) {//Arriba
		if (gunAngle>270) {//Arriba a la derecha
			offsetY -= 2;
			offsetX += 0;
		}
		else {
			offsetY -= 2;
			offsetX += 8;
		}
	}
	else {//Derecha
		offsetY -= 3;
		offsetX += 1;
	}
	offsetY *= Game::getGame()->getScale();
	offsetX *= Game::getGame()->getScale();

	Vector2D gunPos;
	gunPos.setX(mc->getDisplayCenterPos().getX() + offsetX + 12*Game::getGame()->getScale() * gunDirection.getX());
	gunPos.setY(mc->getDisplayCenterPos().getY() + offsetY + 12 * Game::getGame()->getScale() * gunDirection.getY());

	mc->setGunPosition(gunPos);


	return gunAngle;
}
