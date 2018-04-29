#include "RenderWheel.h"



RenderWheel::RenderWheel(GameObject* o) : RenderComponent(o)
{
	wheel = o;
}


RenderWheel::~RenderWheel()
{

}

void RenderWheel::render()
{
	wheel->getCurrentAnimation()->runAnimation();
}
