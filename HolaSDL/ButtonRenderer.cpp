#include "ButtonRenderer.h"



ButtonRenderer::ButtonRenderer(GameObject* o, Texture* normal, Texture* cursorOn, Texture* click, SDL_Rect r): RenderComponent(o), normalTex(normal),
cursorOnTex(cursorOn), clickTex(click), rect(r)
{
	current = ButtonState::normal;
}

ButtonRenderer::~ButtonRenderer()
{
}

void ButtonRenderer::recieveMessage(std::string msg)
{
	if (msg == "cursorOn") 
	{
		current = ButtonState::cursorOn;
	}
	else if (msg == "pressed") 
	{
		current = ButtonState::click;
	}
	else if (msg == "released") 
	{
		current = ButtonState::normal;
	}
}

void ButtonRenderer::render()
{
	switch(current)
	{
	case ButtonState::normal:
		normalTex->render(rect);
		break;
	case ButtonState::cursorOn:
		cursorOnTex->render(rect);
		break;
	case ButtonState::click:
		clickTex->render(rect);
		break;
	}
}
