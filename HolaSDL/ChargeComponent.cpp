#pragma once
#include "ChargeComponent.h"
#include "GameObject.h"
#include "Time.h"
#include "Enemy.h"


ChargeComponent::ChargeComponent(Enemy* o, GameObject* target, float delay, float time, float velMultiplier) : UpdateComponent(o)
{
	e = o;
	chargeDelay = delay;
	chargeTime = time;
	velocityMult = velMultiplier;
	targetObject = target;
	timer = new Timer();
}


ChargeComponent::~ChargeComponent()
{
	delete timer;
}

void ChargeComponent::update() {
	Transform* chaserT = gameObject->getTransform();

	//Si no está cargando comprobamos si el timer ha llegado al delay,
	//si ha llegado charging pasa a ture, guardamos el vector velocidad,
	//multiplicamos speed y reiniciamos el timer
	if (!charging) {
		if (timer->TimeSinceTimerCreation > chargeDelay)
		{
			charging = true;

			auxVel.set(targetObject->getTransform()->position - chaserT->position);
			auxVel.normalize();

			chaserT->speed = e->baseSpeed * velocityMult;
			timer->restart();
		}
		//si no ha llegado aumentamos timer y dejamos al velocidad en 0
		else {
			chaserT->velocity.set(0, 0);
			timer->update();
		}
	}

	//Si está cargando igualamos velocidad a la guardada (para que mantenga la posición)
	// y actualizamos timer
	else {
		if (timer->TimeSinceTimerCreation < chargeTime) {
			//está asignación no tiene efecto porque se sigue llamando al chaseComponent, 
			chaserT->velocity.set(auxVel);
		
			timer->update();
		}
		//Cuando el timer sobrepasa el chargeTime, restauramos el valor de speed, charging pasa
		//a false y reiniciamos el timer
		else {
			timer->restart();
			chaserT->speed = e->baseSpeed;

			//Si lo pones a true carga mas de una vez, en false solo una
			charging = false;
		}
	}

}

void ChargeComponent::startCharge()
{
	gameObject->getTransform()->speed = e->baseSpeed;
	timer->restart();
	charging = false;

}
