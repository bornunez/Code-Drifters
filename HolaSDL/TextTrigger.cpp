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
		PlayState::getInstance()->getMainCharacter()->setMCState(MCState::Idle);
		PlayState::getInstance()->getMainCharacter()->getHook()->setHookStatus(HookStatus::STOP);
		gameObject->setActive(false);
		Game::getGame()->startDialogue(textPath);
		cout << textPath << endl;
	}
}
