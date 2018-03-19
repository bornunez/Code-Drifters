#include "MainMenuState.h"
#include "Game.h"


MainMenuState::MainMenuState()
{
	playButtonTex = new Texture(game->getRenderer(), "..\\images\\playbutton.png", 1,1);
	exitButtonTex = new Texture(game->getRenderer(), "..\\images\\exitbutton.png", 1, 1);
	
	ebPos.h = pbPos.h = 100;
	ebPos.w = pbPos.w = 400;
	ebPos.x = pbPos.x = 200;
	pbPos.y = 350;
	ebPos.y = 475;

	start = new MenuButton(playButtonTex, pbPos, playState);
	exit = new MenuButton(exitButtonTex, ebPos, exitGame);

	gameObjects.push_back(start);
	gameObjects.push_back(exit);

}


MainMenuState::~MainMenuState()
{
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
}

void MainMenuState::update()
{
	for (GameObject* o: gameObjects) 
	{
		o->update();
	}
}

void MainMenuState::render()
{
	SDL_RenderClear(Game::getGame()->getRenderer());
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


