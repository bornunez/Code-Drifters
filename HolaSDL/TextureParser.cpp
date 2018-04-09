#include "TextureParser.h"



TextureParser::TextureParser()
{
}


TextureParser::~TextureParser()
{
}

void TextureParser::parseTextures(string texturesFile)
{

	//Carga y lectura del mapa
	XMLDocument doc;

	doc.LoadFile("cosa.xml");

	// Structure of the XML file:
	// - Element "PLAY"      the root Element, which is the 
	//                       FirstChildElement of the Document
	// - - Element "TITLE"   child of the root PLAY Element
	// - - - Text            child of the TITLE Element

	// Navigate to the title, using the convenience function,
	// with a dangerous lack of error checking.
	string name = doc.FirstChildElement("PATH")->FirstChildElement("NAME")->GetText();
	printf("Name of play (1): %s\n", name);

	// Text is just another Node to TinyXML-2. The more
	// general way to get to the XMLText:
	XMLText* textNode = doc.FirstChildElement("PLAY")->FirstChildElement("TITLE")->FirstChild()->ToText();
	name = textNode->Value();
	printf("Name of play (2): %s\n", name);
}



//
//
//	else
//	{
//		AfxMessageBox("Could not load XML File.");
//		return false;
//	}
//
//
//
//
//	Animation* anim = new Animation(animationName, tileset, o, tileSize*Game::getGame()->getScale(), offsetX, offsetY, loop, time);
//	//Ahora cargamos las tileLayer
//	for (XMLElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
//		if (e->Value() == string("layer"))
//			/*parseTileLayer(root, e, anim, game->getResourceManager()->getCurrTileset());*/
//			parseAnimationLayer(animationName, root, e, anim, ResourceManager::getInstance()->getProtaTileset());
//		if (e->Value() == string("objectgroup")) {
//			string name = e->Attribute("name");
//			if (name == animationName) {
//				parseHitbox(animationName, root, e, anim, o, offsetX, offsetY);
//			}
//		}
//	}
//	//XMLElement* mapa = levelDocument.FirstChildElement("map");
//	//cout << mapa->Attribute("width");
//
//	return anim;
//}
//
