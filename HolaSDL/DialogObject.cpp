#include "DialogObject.h"
#include "Game.h"




DialogObject::DialogObject(string filename )
{
	boxRect = RECT(70, 470, 900, 250);
	namesRect = RECT(150, 510, 150, 50);
	pjRect = RECT(120, 270, 200, 200);
	for (int i = 0; i < 4; i++) 
	{
		SDL_Rect r = RECT(150, 550 + i * 25, 200, 40);
		linesRect.push_back(r);
	}
	string s = "";
	for (int i = 0; i < 4; i++) 
	{
		lines.push_back(s);
	}
	font = new Font("..\\images\\Polentical Neon Bold.ttf", 50);
	box = new Texture(game->getRenderer(), "..\\images\\DialogoSinAnim.png");
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
	currentPhrase = 1;
	read >> i;
	currentPj = i;

	nameTex = new Texture(game->getRenderer());
	nameTex->loadFromText(names[currentPj], *font, { COLOR(0x34D6F6ff) });

	read.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(read, currentText);
	divideText();
	adjustRects();
	for (int i = 0; i < 4; i++) 
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
	int line = 0;
	bool fin = false;
	while (!fin) 
	{
		int max = 0;
		bool nextSpace = false;
		while ((max < 35 || nextSpace)&& !fin) 
		{
			lines[line] += currentText[ch];
			if (nextSpace && currentText[ch]==' ') 
			{
				nextSpace = false;
			}
			max++;
			if (max == 35)
			{
				if (currentText[ch] != ' ')
				{
					nextSpace = true;
				}
			}
			ch++;
			if (ch == currentText.size()) {
				fin = true;
			}
		}
		line++;
	}
}

void DialogObject::adjustRects() 
{
	for (int i = 0; i < 4; i++) 
	{
		linesRect[i].w = lines[i].size() * 15;
	}
	namesRect.w = names[currentPj].length()*18;
	
}

void DialogObject::update()
{
}

void DialogObject::render()
{
	pjSprites[currentPj]->render(pjRect);
	box->render(boxRect);
	nameTex->render(namesRect);
	for (int i = 0; i < linesTex.size(); i++) 
	{
		linesTex[i]->render(linesRect[i]);
	}
}

void DialogObject::handleEvents(SDL_Event & e)
{
	if (e.type == SDL_KEYDOWN) 
	{
		if (e.key.keysym.sym == SDLK_SPACE) 
		{
			currentPhrase++;
			if (currentPhrase <= dialogNum) {
				int i;
				read >> i;
				currentPj = i;
				read.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				getline(read, currentText);
				string s = "";
				for (int i = 0; i < 4; i++)
				{
					lines[i] = s;
				}
				divideText();
				adjustRects();
				nameTex->loadFromText(names[currentPj], *font, { COLOR(0x34D6F6ff) });
				for (int i = 0; i < linesTex.size(); i++)
				{
					linesTex[i]->loadFromText(lines[i], *font);
				}
			}
			else 
			{
				game->endDialogue();
			}
		}
		else if (e.key.keysym.sym == SDLK_ESCAPE) 
		{
			game->endDialogue();
		}
	}
}
