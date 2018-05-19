#pragma once
//#include "checkML.h"
#include "RenderComponent.h"
#include <string>

using namespace std;
class Texture;
class Font;

const float maxScale = 0.75;
const float scaleVel = 0.3;

class PressToInteract :
	public RenderComponent
{
private:
	Texture * pressTex = nullptr;
	Font* font = nullptr;
	SDL_Rect dest;
	float textScale = 1;
	int big = -1; //Indica el sentido de reescalado
public:
	PressToInteract(GameObject* o, string text);
	virtual ~PressToInteract();
	void lateRender();
};

