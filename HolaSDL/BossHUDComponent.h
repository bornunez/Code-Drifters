#pragma once
//#include "checkML.h"
#include"RenderComponent.h"
#include"MasterBoss.h"
#include"HUDObject.h"

class BossHUDComponent:public RenderComponent
{
protected:
	MasterBoss* boss = nullptr;
	HUDObject* bossBar,
		*bossBarBack,	//yellow bar between hp bar and back bar
		*bossBack,
		*bossSkeleton;
public:
	BossHUDComponent(MasterBoss* bossy);
	void lateRender();
	virtual ~BossHUDComponent();
};

