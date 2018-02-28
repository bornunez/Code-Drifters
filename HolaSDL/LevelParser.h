#pragma once
#include <string>
class LevelParser
{
public:
	LevelParser();
	~LevelParser();
	static void loadLevel(std::string fileName);
};

