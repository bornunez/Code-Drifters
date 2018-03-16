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
	TileLayer* tileLayer = new TileLayer(tileset,name,width,height,tileSize);
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
			///cout << t << endl;
			//Decodificamos el mapa
			macaron::Base64::Decode(t, decodedID);
			///cout << decodedID << endl;
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

void AnimationParser::parseHitbox(string animationName, XMLElement * root, XMLElement * hitboxElements, Animation * anim)
{
}

Animation * AnimationParser::parseAnimation(string animationFile, string animationName, GameObject * o, bool loop, float time)
{
	
	//Carga y lectura del mapa
	XMLDocument doc;
	doc.LoadFile(animationFile.c_str());
	//Raiz del mapa
	XMLElement* root = doc.FirstChildElement();
	int tileSize = atoi(root->Attribute("tilewidth"));
	Animation* anim = new Animation(Game::getGame()->getResourceManager()->getProtaTileset(), o, tileSize*Game::getGame()->getScale(), loop, time);
	//Ahora cargamos las tileLayer
	for (XMLElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == string("layer"))
			/*parseTileLayer(root, e, anim, game->getResourceManager()->getCurrTileset());*/
			parseAnimationLayer(animationName,root, e, anim, Game::getGame()->getResourceManager()->getProtaTileset());
		/*if (e->Value() == string("objectgroup")) {
			parseHitbox(animationName, root, e, anim);
		}*/
	}
	//XMLElement* mapa = levelDocument.FirstChildElement("map");
	//cout << mapa->Attribute("width");

	return anim;
}
