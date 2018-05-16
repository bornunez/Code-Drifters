#pragma once
#include "checkML.h"
#include <string>
#include "tinyxml2.h"
#include <vector>
#include "checkML.h"

using namespace tinyxml2;
using namespace std;

class TextureParser
{
public:
	TextureParser();
	~TextureParser();
	static void parseTextures(string textureFile);
};

