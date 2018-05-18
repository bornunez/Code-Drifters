#include "TextTrigger.h"
#include "Game.h"
#include <iostream>

TextTrigger::TextTrigger(GameObject * o, string path) : UpdateComponent(o), textPath(path)
{

}

TextTrigger::~TextTrigger()
{
}

void TextTrigger::update()
{
	if (CollisionHandler::RectCollide(gameObject->getTransform()->body, PlayState::getInstance()->getMainCharacter()->getTransform()->body)) {
		gameObject->setActive(false);
		Game::getGame()->startDialogue(textPath);
		cout << textPath << endl;
	}
}
