#include "MainMenuState.h"
#include "Game.h"
#include "Time.h"
#include <fstream>
#include"ResourceManager.h"
#include "Usabilidad/Tracker.h"

MainMenuState::MainMenuState()
{

	font = new Font("..\\images\\Polentical Neon Regular.ttf", 100);
	font2 = new Font("..\\images\\Polentical Neon Bold.ttf", 100);
	background = new Texture(game->getRenderer(), "..\\images\\Intro\\intro.png");
	op1Tex = new Texture(game->getRenderer());
	op2Tex = new Texture(game->getRenderer());
	op3Tex = new Texture(game->getRenderer());
	op4Tex = new Texture(game->getRenderer());
	EspTex = new Texture(game->getRenderer());
	BarraTex = new Texture(game->getRenderer());
	EngTex = new Texture(game->getRenderer());
	soundOn = new Texture(game->getRenderer(), "..\\images\\NoMuteIcon.png");
	soundOff = new Texture(game->getRenderer(), "..\\images\\MuteIcon.png");

	Language lang = game->getLanguage();
	if (lang == Language::English)
	{
		op1 = "NEW GAME";
		op3 = "CREDITS";
		op4 = "EXIT";
	}
	else 
	{
		op1 = "NUEVO JUEGO";
		op3 = "CREDITOS";
		op4 = "SALIR";
	}
		op2 = "TUTORIAL";
	op1Tex->loadFromText(op1, *font2, white);
	op2Tex->loadFromText(op2, *font2, white);
	op3Tex->loadFromText(op3, *font2, white);
	op4Tex->loadFromText(op4, *font2, white);
	EspTex->loadFromText("ESP ", *font, (lang == Spanish)? blue : white);
	BarraTex->loadFromText("/", *font,white);
	EngTex->loadFromText(" ENG", *font, (lang == English) ? blue : white);

	bckgrndRect = RECT(0, 0, 1040, 720);

	op1Rect = RECT(100, 370, 30 * op1.length(), 70);
	op2Rect = RECT(100, 450, 30 * op2.length(), 70);
	op3Rect = RECT(100, 530, 30 * op3.length(), 70);
	op4Rect = RECT(100, 610, 30 * op4.length(), 70);

	muteRect = RECT(0, 670, 50, 50);


	int langScale = 2;
	EspRect.w = EspTex->getWidth() / langScale; EspRect.h = EspTex->getHeight() / langScale;
	BarraRect.w = BarraTex->getWidth() / langScale; BarraRect.h = BarraTex->getHeight() / langScale;
	EngRect.w = EngTex->getWidth() / langScale; EngRect.h = EngTex->getHeight() / langScale;
	EngRect.x = game->getWinW() - EngRect.w - 20; 
	BarraRect.x = EngRect.x - BarraRect.w; 
	EspRect.x = BarraRect.x - EspRect.w;
	EspRect.y = BarraRect.y = EngRect.y = game->getWinH() - EspRect.h - 20;

	ResourceManager::getInstance()->getMusic(Menu)->play();

}


MainMenuState::~MainMenuState()
{
	delete font;
	delete font2;
	delete background;
	delete op1Tex;
	delete op2Tex;
	delete op3Tex;
	delete op4Tex;
	delete EspTex;
	delete BarraTex;
	delete EngTex;
	delete soundOff;
	delete soundOn;
}

void MainMenuState::handleEvent(SDL_Event & e)
{
if(e.type == SDL_KEYDOWN) 
	{
		if (e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_UP) 
		{
			if (selectedOp == 0) 
			{
				selectedOp = 1;
			}
			else 
			{
				selectedOp--;
				if (selectedOp < 1) 
				{
					selectedOp = 4;
				}
			}
			changeColors();

		}
		else if (e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_DOWN)
		{
			if (selectedOp == 0)
			{
				selectedOp = 1;
			}
			else
			{
				selectedOp++;
				if (selectedOp > 4)
				{
					selectedOp = 1;
				}
			}
			changeColors();

		}
		else if (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_RETURN)
		{
			switch (selectedOp)
			{
			case 1:
				ResourceManager::getInstance()->getMusic(Menu)->stop();
				playState(game, false);
				break;
			case 2:
				ResourceManager::getInstance()->getMusic(Menu)->stop();
				playState(game, true);
				break;
			case 3:
				game->menuCredits();
				break;
			case 4:
				exitGame(game);
				break;
			}
		}
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN) 
	{
		SDL_GetMouseState(&mouse.x, &mouse.y);
		if (SDL_PointInRect(&mouse, &op1Rect) || SDL_PointInRect(&mouse, &op2Rect) || SDL_PointInRect(&mouse, &op3Rect) || SDL_PointInRect(&mouse, &op4Rect)) 
		{
			switch (selectedOp)
			{
			case 1:
				playState(game,false);
				break;
			case 2:
				playState(game, true);
				break;
			case 3:
				game->menuCredits();
				break;
			case 4:
				exitGame(game);
				break;
			}
		}
		else if (SDL_PointInRect(&mouse, &EspRect)) {
			if (game->getLanguage() == English) {
				game->setLanguage(Spanish);
				game->resetMenu();
			}
		}
		else if (SDL_PointInRect(&mouse, &EngRect)) {
			if (game->getLanguage() == Spanish) {
				game->setLanguage(English);
				game->resetMenu();
			}
		}
		else if (SDL_PointInRect(&mouse, &muteRect))
		{
			game->muteGame();
		}
	}
}

void MainMenuState::update()
{

		SDL_GetMouseState(&mouse.x, &mouse.y);
		if (SDL_PointInRect(&mouse, &op1Rect)&& selectedOp!=1)
		{			
			selectedOp = 1;
			changeColors();
		}
		else if (SDL_PointInRect(&mouse, &op2Rect) && selectedOp != 2)
		{
			selectedOp = 2;
			changeColors();
		}
		else if (SDL_PointInRect(&mouse, &op3Rect) && selectedOp != 3)
		{
			selectedOp = 3;
			changeColors();
		}
		else if (SDL_PointInRect(&mouse, &op4Rect) && selectedOp != 4)
		{
			selectedOp = 4;
			changeColors();
		}
		
	for (GameObject* o: gameObjects) 
	{
		o->update();
	}
}

void MainMenuState::render()
{
	SDL_RenderClear(Game::getGame()->getRenderer());
	background->render(bckgrndRect);
		op1Tex->render(op1Rect);
		op2Tex->render(op2Rect);
		op3Tex->render(op3Rect);
		op4Tex->render(op4Rect);
		EspTex->render(EspRect);
		BarraTex->render(BarraRect);
		EngTex->render(EngRect); 
		if (game->getMute())
		{
			soundOff->render(muteRect);
		}
		else
		{
			soundOn->render(muteRect);
		}
	for (GameObject* o : gameObjects) 
	{
		o->render();
	}

}

void MainMenuState::playState(Game* game,bool tutorial)
{
	game->playIntro(tutorial);
}

void MainMenuState::exitGame(Game* game)
{
	game->exit = true;
}

void MainMenuState::changeColors() 
{
	if (selectedOp == 1)
	{
		op1Tex->loadFromText(op1, *font2, blue);
		op2Tex->loadFromText(op2, *font2, white);
		op3Tex->loadFromText(op3, *font2, white);
		op4Tex->loadFromText(op4, *font2, white);
	}
	else if (selectedOp == 2)
	{
		op2Tex->loadFromText(op2, *font2, blue);
		op1Tex->loadFromText(op1, *font2, white);
		op3Tex->loadFromText(op3, *font2, white);
		op4Tex->loadFromText(op4, *font2, white);
	}
	else if (selectedOp == 3)
	{
		op3Tex->loadFromText(op3, *font2, blue);
		op2Tex->loadFromText(op2, *font2, white);
		op1Tex->loadFromText(op1, *font2, white);
		op4Tex->loadFromText(op4, *font2, white);
	}
	else if (selectedOp == 4)
	{
		op4Tex->loadFromText(op4, *font2, blue);
		op2Tex->loadFromText(op2, *font2, white);
		op3Tex->loadFromText(op3, *font2, white);
		op1Tex->loadFromText(op1, *font2, white);
	}


}



