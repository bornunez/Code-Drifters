#include "ButtonRenderer.h"



ButtonRenderer::ButtonRenderer(GameObject* o, Texture* normal, Texture* cursorOn, Texture* click): RenderComponent(o), normalTex(normal),
cursorOnTex(cursorOn), clickTex(click)
{
	current = ButtonState::normal;
}

ButtonRenderer::~ButtonRenderer()
{
}

void ButtonRenderer::recieveMessage(std::string msg)
{

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
