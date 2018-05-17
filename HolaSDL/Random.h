#pragma once
//#include "checkML.h"
#include <vector>

using namespace std;
class Random
{
public:
	Random();
	~Random();

	//Devuelve un random Int entre "min" y "max", incluidos
	static int randomInt(int min, int max);

	//Devuelve un random Float entre "min" y "max", incluidos, y con "numDecimales" decimales
	static float randomFloat(float min, float max, int numDecimales);

	static string fraseAleatoria();
private:
};

