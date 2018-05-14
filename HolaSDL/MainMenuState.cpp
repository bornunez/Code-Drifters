#include "MainMenuState.h"
#include "Game.h"


MainMenuState::MainMenuState()
{

	font = new Font("..\\images\\Polentical Neon Regular.ttf", 100);
	//playButtonTex = new Texture(game->getRenderer(), "..\\images\\playbutton.png", 1,1);
	exitButtonTex = new Texture(game->getRenderer(), "..\\images\\exitbutton.png", 1, 1);
	background = new Texture(game->getRenderer(), "..\\images\\Intro\\intro.png");
	openText = new Texture(game->getRenderer());
	c.a = 0;
	c.b = 200;
	c.g = 50;
	c.r = 200;

	ebPos.h = 75;
	ebPos.w = 75;
	ebPos.x = 0;
	ebPos.y = 645;

	bckgrndRect = RECT(0, 0, 1040, 720);
	textRect = RECT(320, 555, 450, 70);

	//start = new MenuButton(playButtonTex, pbPos, playState);
	exit = new MenuButton(exitButtonTex, ebPos, exitGame);

	//gameObjects.push_back(start);
	gameObjects.push_back(exit);

}


MainMenuState::~MainMenuState()
{
	delete font;
	delete exitButtonTex;
	delete background;
	delete openText;
	delete exit;
}

void MainMenuState::handleEvent(SDL_Event & e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		for (GameObject* o : gameObjects)
		{
			o->handleEvents(e);
		}
	}
	else if (e.type == SDL_KEYDOWN) 
	{
		playState(game);
	}
}

void MainMenuState::update()
{
	if (!alfaUp) 
	{
		c.r-=4;
		c.b-=4;
		c.g--;
		if (c.r == 0) 
		{
			alfaUp = true;
		}
	}
	else 
	{
		c.r+=4;
		c.b+=4;
		c.g++;
		if (c.r == 200)
		{
			alfaUp = false;
		}
	}
	openText->loadFromText("Press any Key to continue", *font, c);
	for (GameObject* o: gameObjects) 
	{
		o->update();
	}
}

void MainMenuState::render()
{
	SDL_RenderClear(Game::getGame()->getRenderer());
	background->render(bckgrndRect);
	openText->render(textRect);
	for (GameObject* o : gameObjects) 
	{
		o->render();
	}
}

void MainMenuState::playState(Game* game)
{
	game->startGame();
}

void MainMenuState::exitGame(Game* game)
{
	game->exit = true;
}


