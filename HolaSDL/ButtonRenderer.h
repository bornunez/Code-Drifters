#pragma once
#include "RenderComponent.h"
#include "ResourceManager.h"

enum ButtonState{normal, cursorOn, click};
class ButtonRenderer: public RenderComponent
{
private:
	Texture* normalTex;
	Texture* cursorOnTex;
	Texture* clickTex;
	SDL_Rect rect;
	ButtonState current;
public:
	ButtonRenderer(GameObject* o, Texture* normal, Texture* cursorOn, Texture* click);
	~ButtonRenderer();

	void recieveMessage(std::string msg);
	void render();
};

