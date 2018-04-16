#include "ReloadComponent.h"
#include "MainCharacter.h"
#include "Time.h"

ReloadComponent::ReloadComponent(MainCharacter* mc) : UpdateComponent(mc), mc(mc)
{
}


ReloadComponent::~ReloadComponent()
{
}

void ReloadComponent::update()
{
	if (active) {
		float reloadT =( 1.0 / mc->getReloadTime()) * Time::getInstance()->DeltaTime;
		float currB = mc->getCurrentBullets();
		currB += reloadT;
		//Si sobrepasa las balas maximas, lo dejamos en la maxima
		if (currB > mc->getMaxBullets()) {
			currB = mc->getMaxBullets();
		}
		cout << "BulletTime [ " << currB << " ]" << endl;
		mc->setCurrentBullets(currB);
	}
}

void ReloadComponent::restart()
{
	active = true;
	mc->setReloadTime( 0);
}
