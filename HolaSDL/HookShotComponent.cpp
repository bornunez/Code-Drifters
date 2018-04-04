#include "HookShotComponent.h"
#include "GameObject.h"
#include "Hook.h"
#include <iostream>
#include "PlayState.h"
#include "MainCharacter.h"
#include "Time.h"
HookShotComponent::HookShotComponent(MainCharacter* mc, Hook* h, float hookSpeed) : UpdateComponent(static_cast<GameObject*>(h))
{
	h->setActive(false);
	hook = h;
	this->hookSpeed = hookSpeed;
	this->mc = mc;
}

HookShotComponent::~HookShotComponent()
{
}

void HookShotComponent::update()
{
	if (hook->isActive()) {
		Vector2D hookSize = hook->getTransform()->position - hook->getOriginPosition();//Diferencia entre la pos actual del gancho y su origen
		
		if (hook->getHookStatus() == EXTEND) {
			if (hookSize.magnitude() < hook->getLength()) {
				extend();
			}
			else {
				hook->setHookStatus(CONTRACT);
			}
		}		
		else if (hook->getHookStatus() == CONTRACT) {
			if (hookSize.magnitude() > 10) {//10 margen de error MEJOR HACERLO POR COLISIÓN CON EL PERSONAJE
				contract();
			}
			else {
				hook->setHookStatus(STOP);
				hook->setActive(false);
			}
		}
	}
}

void HookShotComponent::shoot(Vector2D originPos, Vector2D hookDir)
{
	PlayState::getInstance()->addGameObject(hook);
	hook->setActive(true);
	hook->setOriginPosition(originPos);
	hook->getTransform()->position.set(originPos);
	hook->getTransform()->velocity.set(hookDir);
	hook->setHookStatus(EXTEND);
	mc->setActionState(Hooking);
}

void HookShotComponent::extend()
{
	Transform* t = hook->getTransform();
	t->position.set(t->position + t->velocity*hookSpeed*(Time::getInstance()->DeltaTime));
	t->body.x = t->position.getX(); t->body.y = t->position.getY();
}

void HookShotComponent::contract()
{
	Transform* t = hook->getTransform();
	t->position.set(t->position - t->velocity*hookSpeed*(Time::getInstance()->DeltaTime));
	t->body.x = t->position.getX(); t->body.y = t->position.getY();
}

void HookShotComponent::stop()
{
}


