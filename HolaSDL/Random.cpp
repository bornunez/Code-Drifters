#include "Random.h"
#include <random>
#include <math.h>
#include<time.h>
#include<fstream>
#include <string>


Random::Random()
{
}

Random::~Random()
{
}

int Random::randomInt(int min, int max)
{
	srand((unsigned)time(NULL));

	int rando = 0;

	rando = rand() % (max+1 - min) + min;
	return rando;
}

float Random::randomFloat(float min, float max, int decimales)
{
	srand((unsigned)time(NULL));

	int rando = 0;

	int minimo = min*(pow(10, decimales));
	int maximo = max*(pow(10, decimales));

	rando = (rand() % (maximo + 1 - minimo) + minimo) / (pow(10, decimales));

	return rando;
}

string Random::fraseAleatoria()
{
	string frase;
	vector<string> frases;
	ifstream archivo;
	archivo.open("..\\FrasesAleatorias.txt");
	while (!archivo.eof())
	{
		getline(archivo, frase);
		frases.push_back(frase);
	}
	int rando = randomInt(0, frases.size()-1);
	frase = frases[rando];
	archivo.close();
	return frase;
}


