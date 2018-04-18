#include "AnimationParser.h"
#include "LevelParser.h"
#include "Map.h"
#include "Base64.h"
#include "miniz.h"
#include "Game.h"
#include "PlayState.h"
#include "ResourceManager.h"
#include "EnemyManager.h"
#include "Animation.h"



AnimationParser::~AnimationParser()
{
}

void AnimationParser::parseAnimationLayer(string animationName, XMLElement * root, XMLElement * animationElement, Animation * anim, Tileset * tileset)
{
	
	//Cargamos los datos del mapa
	int tileSize = atoi(root->Attribute("tilewidth"));
	int width = atoi(root->Attribute("width"));
	int height = atoi(root->Attribute("height"));
	string name = animationElement->Attribute("name");
	TileLayer* tileLayer = new TileLayer({ tileset }, name, width, height, tileSize);
	//Vector de los datos de tiles
	vector<vector<int>> data;
	string decodedID;
		//Nodo donde estaguardado el mapa
	XMLElement* dataNode = animationElement->FirstChildElement("data");

	for (XMLNode* e = dataNode->FirstChild(); e != nullptr; e = e->NextSibling())//Esto hay que pasarlo a While
	{
		//Entra al hijo que tenga el nombre que buscamos
		if (name == animationName) {


			XMLText* text = e->ToText();
			std::string t = text->Value();
			//Quitar los espacios ( Lee la linea con espacios incluidos) Esto es un hack
			string nt;
			for (int i = 0; i < t.length(); i++) {
				if (t[i] != '\n' &&t[i] && t[i] != ' ') {
					nt.push_back(t[i]);
				}
			}
			t = nt;
			//Aqui ya esta el texto cortado y listo para decodificar
			//Decodificamos el mapa
			macaron::Base64::Decode(t, decodedID);
			//Y descomprimimos
			uLongf numGids = width * height * sizeof(int);
			std::vector<unsigned> gids(numGids);
			uncompress((Bytef*)&gids[0], &numGids, (const Bytef*)decodedID.c_str(), decodedID.size());
			std::vector<int> layerRow(width);
			//Ajustamos el tamaño del vector
			for (int j = 0; j < height; j++)
			{
				data.push_back(layerRow);
			}
			//Y asignamos a cada dato de la matriz la informacion del tile
			for (int rows = 0; rows < height; rows++)
			{
				for (int cols = 0; cols < width; cols++)
				{
					data[rows][cols] = gids[rows * width + cols];
				}
			}
			//Finalmente lo asignamos a la layer y la agregamos al vector de layers
			tileLayer->seTileIDs(data);
			anim->setLayer(tileLayer);
		}
	}
}

void AnimationParser::parseHitbox(string animationName, XMLElement * root, XMLElement * hitboxElements, Animation * anim, GameObject* o, int offsetX, int offsetY)
{
	//Nodo donde estaguardado el mapa
	for (XMLElement* e = hitboxElements->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		//Leemos los atributos 
		int width = atoi(e->Attribute("width"));
		int height = atoi(e->Attribute("height"));
		int x = atoi(e->Attribute("x"));
		int y = atoi(e->Attribute("y"));
		int frame = atoi(e->Attribute("type"));
		string type = string(e->Attribute("name"));
		
		SDL_Rect box;
		box.w = width * Game::getGame()->getScale();
		box.h = height * Game::getGame()->getScale();
		box.x = x;
		box.y = y;
		
		//El offset del hitbox respecto al sprite
		int offsetx = ((x) % 64)* Game::getGame()->getScale() + offsetX;
		int offsety = ((y) % 64)* Game::getGame()->getScale() + offsetY;
		if (type == "Hitbox") {
			anim->getFrame(frame)->addHitbox(box,offsetx,offsety);
		}
		else if (type == "Hurtbox") {
			anim->getFrame(frame)->addHurtbox(box,offsetx,offsety);
		}
		else if (type == "Hithurtbox") {
			anim->getFrame(frame)->addHurtbox(box, offsetx, offsety);
			anim->getFrame(frame)->addHitbox(box, offsetx, offsety);
		}
		else if(type == "GunPosition"){
			Vector2D gunPos;
			gunPos.setX(x);
			gunPos.setY(y);
			anim->getFrame(frame)->addGunPosition(gunPos,offsetx,offsety);
		}
		
		//Ahora leemos las propiedades 
		//vector<string> enemyTypes;
		//XMLElement* propElement = e->FirstChildElement("properties");
		////Por cada propiedad, si su valor es true, añadimos el enemigo al vector
		//for (XMLElement* p = propElement->FirstChildElement(); p != nullptr; p = p->NextSiblingElement()) {
		//	if (p->Attribute("value") == string("true"))
		//		enemyTypes.push_back(p->Attribute("name"));
		//}
		////Ahora cogemos un enemigo aleatorio
		//if (enemyTypes.size() > 0) {
		//	int randEnemy = rand() % enemyTypes.size();
		//	//Lo parseamos
		//	EnemyType eType = parseEnemyTypes(enemyTypes[randEnemy]);
		//	Spawner* spawner = new Spawner(x*Game::getGame()->getScale(), y*Game::getGame()->getScale(), eType);
		//	map->addSpawn(spawner);
		//}
	}
}

Animation * AnimationParser::parseAnimation(Tileset* tileset, string animationFile, string animationName, GameObject * o, int offsetX, int offsetY,bool loop, float time )
{
	
	//Carga y lectura del mapa
	XMLDocument doc;
	doc.LoadFile(animationFile.c_str());
	//Raiz del mapa
	XMLElement* root = doc.FirstChildElement();
	int tileSize = atoi(root->Attribute("tilewidth"));
	Animation* anim = new Animation(animationName, tileset, o, tileSize, offsetX, offsetY, loop, time);
	//Ahora cargamos las tileLayer
	for (XMLElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == string("layer"))
			//parseTileLayer(root, e, anim, game->getResourceManager()->getCurrTileset());
			parseAnimationLayer(animationName,root, e, anim, tileset);
		if (e->Value() == string("objectgroup")) {
			string name = e->Attribute("name");
			if (name == animationName) {
				parseHitbox(animationName, root, e, anim, o, offsetX, offsetY);
			}
		}
	}
	//XMLElement* mapa = levelDocument.FirstChildElement("map");

	return anim;
}
