#pragma once
#include "ChaseComponent.h"
#include "GameObject.h"
#include "Time.h"
#include "Enemy.h"

ChaseComponent::ChaseComponent(Enemy* o, GameObject* target, float distance) : UpdateComponent(o)
{
	targetObject = target;
	distancia = distance;
	ec = o;

}


ChaseComponent::~ChaseComponent()
{
}

void ChaseComponent::update() {
	
	if (angle > 365) angle = 0;

	//Obtienes transfroms de enemigo y objetivo (por limpieza)
	Transform* chaserT = gameObject->getTransform();
	Transform* targetT = targetObject->getTransform();


	Vector2D auxVel;
	Vector2D auxPos;
	if ((abs(targetT->position.getX() - chaserT->position.getX() - 25) + abs(targetT->position.getY() - chaserT->position.getY() - 25)) <= distancia + 50) {
		if (!rotating) {
			rotating = true;
			chaserT->speed *= (float)(rand()%50 + 20)/(float)100;
			angle = targetT->position.angle(chaserT->position);
		}
		//Circular Movement
		//Auxpos marca punto en trayectoria circular alrededor del target, bomber asume esa position como target y lo persigue
		angle += Time::getInstance()->DeltaTime*2;
		auxPos.set(targetT->position.getX() - 25 + cos(angle)*(distancia - 50), targetT->position.getY() - 25 + sin(angle)*(distancia - 50));
		auxVel.set(auxPos - chaserT->position);
		auxVel.normalize();
		chaserT->velocity.set(auxVel);

	}

	//Persecucion normal
	else if ((abs(targetT->position.getX() - chaserT->position.getX()) + abs(targetT->position.getY() - chaserT->position.getY())) 
		>=(abs(targetT->body.w - chaserT->body.w) +abs(targetT->body.h - chaserT->body.h))) {
		
		if (rotating) {
			chaserT->speed = ec->baseSpeed;
			rotating = false;
		}
		//vectorentre enemigo y objetivo
		auxVel.set(targetT->position - chaserT->position);

		//se normaliza 
		auxVel.normalize();

	}
	else {
		auxVel.set(0, 0);
	}
	//se asigna la velocidad del enemigo 
	chaserT->velocity.set(auxVel);
}

