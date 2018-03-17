#pragma once
#include <string>
#include "tinyxml2.h"
#include "Tileset.h"
#include "Layer.h"
#include "TileLayer.h"
#include <vector>

class Camera;
enum EnemyType;
using namespace tinyxml2;
using namespace std;
class Animation;
class AnimationParser
{
public:
	AnimationParser() {};
	~AnimationParser();

private:
	static void parseAnimationLayer(string animationName, XMLElement* root, XMLElement* animationElement, Animation* anim, Tileset* tileset);
	static void parseHitbox(string animationName, XMLElement* root, XMLElement* hitboxElements, Animation* anim, GameObject* o, int offsetX, int offsetY);
public:
	static Animation* parseAnimation(string animationFile, string animationName, GameObject* o, int offsetX=0, int offsetY=0,bool loop=true, float time=0.05);
};

