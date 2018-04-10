#include "DialogObject.h"
#include "Game.h"




DialogObject::DialogObject(string filename )
{
	boxRect = RECT(120, 470, 800, 250);
	namesRect = RECT(150, 480, 150, 50);
	pjRect = RECT(120, 120, 200, 350);
	for (int i = 0; i < 4; i++) 
	{
		SDL_Rect r = RECT(150, 510 + i * 60, 200, 40);
		linesRect.push_back(r);
	}
	string s = "";
	for (int i = 0; i < 4; i++) 
	{
		lines.push_back(s);
	}
	font = new Font("..\\images\\ARCADECLASSIC.ttf", 50);
	box = new Texture(game->getRenderer(), "..\\images\\MCbullet.png");
	read.open("..\\dialogues\\" + filename + ".txt");
	read >> pjNum;
	string aux;
	for (int i = 0; i < pjNum; i++) 
	{
		read >> aux;
		Texture* t = new Texture(game->getRenderer(), "..\\images\\" + aux + ".png");
		pjSprites.push_back(t);
		read >> aux;
		names.push_back(aux);
	}
	int i;
	read >>i;
	dialogNum = i;
	read >> i;
	currentPj = i;
	nameTex = new Texture(game->getRenderer());
	nameTex->loadFromText(names[currentPj], *font);
	getline(read, currentText);
	divideText();
	adjustRects();
	for (int i = 0; i < linesTex.size(); i++) 
	{
		Texture* t = new Texture(game->getRenderer());
		linesTex.push_back(t);
		linesTex[i]->loadFromText(lines[i], *font);
	}


}


DialogObject::~DialogObject()
{
	delete font;
	delete box;
	delete nameTex;
	for (int i = 0; i < linesTex.size(); i++) 
	{
		delete linesTex[i];
	}
	for (int i = 0; i <pjSprites.size(); i++)
	{
		delete pjSprites[i];
	}
	read.close();
}
void DialogObject::divideText()
{
	int ch = 0;
	int mark = 0;
	int line = 0;
	bool fin = false;
	while (!fin) 
	{
		int max = 0;
		bool nextSpace = false;
		while ((max < 20 || nextSpace)&& !fin) 
		{
			lines[line][mark] = currentText[ch];
			if (nextSpace && currentText[ch]==' ') 
			{
				nextSpace = false;
			}
			max++;
			if (max == 20)
			{
				if (currentText[ch] != ' ')
				{
					nextSpace = true;
				}
			}
			ch++; mark++;
			if (ch == currentText.size()) {
				fin = true;
			}
		}
		line++; mark = 0;
	}
}

void DialogObject::adjustRects() 
{
	for (int i = 0; i < 4; i++) 
	{
		linesRect[i].w = lines[i].size() * 5;
	}
}

void DialogObject::update()
{
}

void DialogObject::render()
{
	//SDL_RenderClear(game->getRenderer());
	pjSprites[currentPj]->render(pjRect);
	box->render(boxRect);
	nameTex->render(namesRect);
	for (int i = 0; i < linesTex.size(); i++) 
	{
		linesTex[i]->render(linesRect[i]);
	}
	//SDL_RenderPresent(game->getRenderer());
}

void DialogObject::handleEvents(SDL_Event & e)
{
	if (e.type == SDL_KEYDOWN) 
	{
		if (e.key.keysym.sym == SDLK_SPACE) 
		{
			int i;
			read >> i;
			currentPj = i;
			getline(read, currentText);
			divideText();
			adjustRects();
			nameTex->loadFromText(names[currentPj], *font);
			for (int i = 0; i < linesTex.size(); i++)
			{
				linesTex[i]->loadFromText(lines[i], *font);
			}
		}
	}
}
