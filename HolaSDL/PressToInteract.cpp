#include "PressToInteract.h"
#include "PlayState.h"
#include "CollisionHandler.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Font.h"
#include "Game.h"

PressToInteract::PressToInteract(GameObject* o) : RenderComponent(o)
{
	Game* g = Game::getGame();
	font = new Font("..\\images\\Polentical Neon Bold.ttf", 50);
	pressTex = new Texture(g->getRenderer());
	pressTex->loadFromText("PRESS E TO ENTER THE SHOP", *font, { COLOR(0x7e7effff) });
	dest.h = pressTex->getHeight() * g->getScale(); dest.w = pressTex->getWidth() * g->getScale();
}


PressToInteract::~PressToInteract()
{
}

void PressToInteract::lateRender()
{
	textScale += big * scaleVel * Time::getInstance()->DeltaTime;
	if (textScale <= maxScale) {
		textScale = maxScale;
		big = 1;
	}
	else if (textScale >= 1) {
		textScale = 1;
		big = -1;
	}

	if (CollisionHandler::RectCollide(gameObject->getTransform()->body, PlayState::getInstance()->getMainCharacter()->getTransform()->body)) {
		dest.h = pressTex->getHeight() * textScale;
		dest.w = pressTex->getWidth() * textScale;
		dest.x = (Game::getGame()->getWinW() - dest.w) / 2; dest.y = (Game::getGame()->getWinH() - (Game::getGame()->getWinH() / 8)) - dest.h/2;
		pressTex->render(dest);
	}
}
