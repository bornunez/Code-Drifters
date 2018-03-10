//#pragma once
//#include "TestGame.h"
//#include "GameStateMachine.h"
//#include "Camera.h"
//#include "MainCharacter.h"
//#include "DungeonGenerator.h"
//#include "CameraMovementComponent.h"
//#include "ExampleEnemy.h"
//#include "ResourceManager.h"
//#include "MouseIcon.h"
//#include "MCMovementComponent.h"
//#include "DungeonGenerator.h"
//#include "Room.h"
//#include "LevelParser.h"
//#include "Map.h"
//#include "PlayState.h"
//#include "TestState.h"
//TestGame::TestGame()
//{
//}
//TestGame::~TestGame()
//{
//	delete stateMachine;
//	SDL_DestroyRenderer(renderer);
//	SDL_DestroyWindow(window);
//	SDL_Quit();
//
//}
//
//SDL_Renderer * TestGame::getRenderer()
//{
//	return renderer;
//}
//
//
//void TestGame::run()
//{
//	while (!exit)
//	{
//		//Provisional en lugar del render
//
//		stateMachine->currentState()->update();
//		stateMachine->currentState()->render();
//		handleEvents();
//		this->mouseIcon->drawIcon(event);
//		SDL_RenderPresent(dynamic_cast<Game*>(this)->getRenderer());
//	}
//}
//
//void TestGame::handleEvents()
//{
//	while (SDL_PollEvent(&event) && !exit) {
//
//		if (event.type == SDL_KEYDOWN) {
//			if (event.key.keysym.sym == SDLK_ESCAPE) {
//				exit = true;
//			}
//			else if (event.key.keysym.sym == SDLK_F11) {
//
//				if (fullScreen) {
//					fullScreen = false;
//					SDL_SetWindowFullscreen(window, SDL_FALSE);
//				}
//				else {
//					fullScreen = true;
//					SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
//				}
//			}
//		}
//		if (event.type == SDL_QUIT)
//		{
//			exit = true;
//		}
//
//		else
//		{
//			stateMachine->currentState()->handleEvent(event);
//		}
//	}
//}
//
//int TestGame::getWinW() {//Pide el ancho de la ventana
//	return winWidth;
//}
//int TestGame::getWinH() {//Pide la altura de la altura
//	return winHeight;
//}
