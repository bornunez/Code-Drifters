#include "Shop.h"
#include "Game.h"



Shop::Shop(ShopState* shopState)
{
	//lecture of different trees from file
	for (int i = 0; i < 3; i++) {
		Skills_[i] = new SkillTree(nullptr, "..\\Arbol\\" + to_string(i + 1) + ".txt", "..\\Arbol\\Textures\\"+ to_string(i+1) +".png", shopState);
		fondos_[i] = new Texture(Game::getGame()->getRenderer());
	}
	//lecture of textures
	if (!LoadTextures());
	
	right_tree.w = left_tree.w = 200;
	right_tree.h = left_tree.h = 400;
	central_tree.w = 400; 
	central_tree.h = 550;

	right_tree.y = left_tree.y = 150;
	central_tree.y = 50;

	left_tree.x = 140;
	central_tree.x = left_tree.x + left_tree.w - 25;
	right_tree.x = central_tree.x + central_tree.w-25;

	/*SDL_Rect aux;
	aux.w = aux.h = 75;
	aux.x = 50;
	aux.y = 300;
	Left = new Button(aux, GoLeft, "..\\images\\background1.png", rend);
	aux.x = 650;
	Right = new Button(aux, GoRight, "..\\images\\background1.png", rend);-*/
}

bool Shop::LoadTextures() {
	if (!fondos_[0]->loadFromImg("..\\Arbol\\Izquierdo.png")) return false;
	if (!fondos_[1]->loadFromImg("..\\Arbol\\Central.png"))return false;
	if (!fondos_[2]->loadFromImg("..\\Arbol\\Derecho.png"))return false;
	else return true;
}

Shop::~Shop()
{
}

void Shop::update() {

}

void Shop::render() {
	//render of the left and right rectangles
	fondos_[(actual_tree + 1) % 3]->render(right_tree);
	fondos_[(actual_tree + 2) % 3]->render(left_tree);

	//render of left and right tree, in the assigned rectangle
	Skills_[(actual_tree + 1) % 3]->render(right_tree, 30, right_tree.w);
	Skills_[(actual_tree + 2) % 3]->render(left_tree, 30, left_tree.w);


	//render of the central tree, so it is above the two others
	fondos_[actual_tree]->render(central_tree);
	Skills_[actual_tree]->render(central_tree, 55, central_tree.w);
}

void Shop::handleEvents(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN) {
		if (e.key.keysym.sym == SDLK_RIGHT) {
			GoRight();
			//cout << actual_tree << endl;
		}
		else if (e.key.keysym.sym == SDLK_LEFT) {
			GoLeft();
			//cout << actual_tree << endl;
		}
	}
	//Left_->HandleEvents(e);
	//Right_->HandleEvents(e);
	Skills_[actual_tree]->HandleEvents(e);
}
