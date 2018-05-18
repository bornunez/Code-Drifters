#pragma once
#include "ResourceManager.h"
#include "Tileset.h"
#include "tinyxml2.h"
#include "Game.h"

using namespace tinyxml2;

//Inicializacion de instance
ResourceManager* ResourceManager::instance = nullptr;

//Ver si declararle un renderer propio o usar el de game
ResourceManager::ResourceManager(SDL_Renderer* renderer) : numOfMusic(0), music(nullptr), numOfSoundEffects(0), soundEffects(nullptr)
{
	this->renderer = renderer;
	loadTextures();
	setMusic(musicFiles);
	setSoundEffects(soundEffectFiles);
	loadProtaTileset();
	loadEnemyTilesets();
	loadBoss1Tilesets();
	loadBoss2Tilesets();
	loadBoss3Tilesets();

}

void ResourceManager::createInstance(SDL_Renderer * renderer)
{
	if (instance == nullptr)	
		instance = new ResourceManager(renderer);
}

ResourceManager::~ResourceManager()
{
	closeTilesets();
	closeSoundEffects();
	closeMusic();
	closeTextures();
}

void ResourceManager::ResetInstance() 
{
	delete instance;
	instance = nullptr;
}
Texture * ResourceManager::getTexture(TextureId id)
{
	if (id < NUM_TEXTURES)
		return textures[id];
	else
		return nullptr;
}

Tileset * ResourceManager::getTileset(string path)
{
	//Hay que limpiar el path de ../../  
	int i = 0;
	while (path[i] == '/' || path[i] == '.')
		i++;
	//Una vez eliminados, copiamos el nuevo string
	string auxPath;
	for (i; i < path.size(); i++)
		auxPath.push_back(path[i]);
	path = auxPath;

	for (size_t i = 0; i < tilesets.size(); i++)
	{
		if (tilesets[i]->getPath() == path)
			return tilesets[i];
	}

	Tileset* aux = loadTileset(path);
	return aux;
}

void ResourceManager::loadTextures()
{
	for (int i = 0; i < NUM_TEXTURES; i++) {
		const TextureAtributes atributes = TEXTURE_ATRIBUTES[i];
		textures[i] = new Texture(renderer, TEXT_PATH + atributes.filename, atributes.numRows, atributes.numCols);
	}
}

void ResourceManager::closeTextures() {
	for (int i = 0; i < NUM_TEXTURES; i++) {
		if (textures[i] != nullptr) {
			delete textures[i];
		}
	}
	//delete[] textures;
}

void ResourceManager::closeTilesets() {
	for (Tileset* obj : tilesets)
		delete obj;
	tilesets.clear();

	for (Tileset* obj : protaTileset)
		delete obj;
	protaTileset.clear();

	for (Tileset* obj : enemyTilesets)
		delete obj;
	enemyTilesets.clear();

	for (Tileset* obj : boss1Tilesets)
		delete obj;
	boss1Tilesets.clear();

	for (Tileset* obj : boss2Tilesets)
		delete obj;
	boss2Tilesets.clear();

	for (Tileset* obj : boss3Tilesets)
		delete obj;
	boss3Tilesets.clear();
}

Tileset* ResourceManager::loadTileset(string path)
{
		
		string filename = path;
		XMLDocument doc;
		doc.LoadFile((TILESET_PATH + filename).c_str());
		//Raiz del tileset
		XMLElement* root = doc.FirstChildElement();
		string imageSrc = root->FirstChildElement("image")->Attribute("source");
		Texture* tileTex = new Texture(Game::getGame()->getRenderer(), TILESET_PATH + "tileset/" + imageSrc);
		//Y cargamos el tileset
		Tileset* aux = new Tileset(tileTex, root);
		aux->setPath(path);
		tilesets.push_back(aux);
		return aux;
}

void ResourceManager::loadProtaTileset()
{
	for (int i = 0; i < NUM_PROTATILESET; i++) {
		string filename = protaTilesetName[i];
		XMLDocument doc;
		doc.LoadFile((PROTATILESET_PATH + filename).c_str());
		//Raiz del tileset
		XMLElement* root = doc.FirstChildElement();
		string imageSrc = root->FirstChildElement("image")->Attribute("source");
		Texture* tileTex = new Texture(renderer, PROTATILESET_PATH + imageSrc);
		//Y cargamos el tileset
		protaTileset.push_back( new Tileset(tileTex, root));
	}
}

void ResourceManager::loadEnemyTilesets()
{
	for (int i = 0; i < NUM_ENEMYTILESET; i++) {
		string filename = enemyTilesetNames[i];
		XMLDocument doc;
		doc.LoadFile((ENEMY_PATH + filename).c_str());
		//Raiz del tileset
		XMLElement* root = doc.FirstChildElement();
		string imageSrc = root->FirstChildElement("image")->Attribute("source");
		Texture* tileTex = new Texture(renderer, ENEMY_PATH + imageSrc);
		//Y cargamos el tileset
		enemyTilesets.push_back(new Tileset(tileTex, root));
	}
}

void ResourceManager::loadBoss1Tilesets()
{
	for (int i = 0; i < NUM_BOSS1TILESET; i++) {
		string filename = boss1TilesetNames[i];
		XMLDocument doc;
		doc.LoadFile((BOSS1_PATH + filename).c_str());
		//Raiz del tileset
		XMLElement* root = doc.FirstChildElement();
		string imageSrc = root->FirstChildElement("image")->Attribute("source");
		Texture* tileTex = new Texture(renderer, BOSS1_PATH + imageSrc);
		//Y cargamos el tileset
		boss1Tilesets.push_back(new Tileset(tileTex, root));
	}
}
void ResourceManager::loadBoss2Tilesets()
{
	for (int i = 0; i < NUM_BOSS2TILESET; i++) {
		string filename = boss2TilesetNames[i];
		XMLDocument doc;
		doc.LoadFile((BOSS2_PATH + filename).c_str());
		//Raiz del tileset
		XMLElement* root = doc.FirstChildElement();
		string imageSrc = root->FirstChildElement("image")->Attribute("source");
		Texture* tileTex = new Texture(renderer, BOSS2_PATH + imageSrc);
		//Y cargamos el tileset
		boss2Tilesets.push_back(new Tileset(tileTex, root));
	}
}
void ResourceManager::loadBoss3Tilesets()
{
	for (int i = 0; i < NUM_BOSS3TILESET; i++) {
		string filename = boss3TilesetNames[i];
		XMLDocument doc;
		doc.LoadFile((BOSS3_PATH + filename).c_str());
		//Raiz del tileset
		XMLElement* root = doc.FirstChildElement();
		string imageSrc = root->FirstChildElement("image")->Attribute("source");
		Texture* tileTex = new Texture(renderer, BOSS3_PATH + imageSrc);
		//Y cargamos el tileset
		boss3Tilesets.push_back(new Tileset(tileTex, root));
	}
}

void ResourceManager::setMusic(std::vector<std::string> musicVect) {
	closeMusic();
	numOfMusic = musicVect.size();
	music = new Music*[numOfMusic];
	for (int i = 0; i < numOfMusic; i++) {
		music[i] = new Music(musicVect[i]);
	}
}

void ResourceManager::closeMusic()
{
	for (int i = 0; i < numOfMusic; i++) {
		if (music[i] != nullptr) {
			delete music[i];
		}
	}
	delete[] music;
	numOfMusic = 0;
}

Music* ResourceManager::getMusic(MusicId i) const {
	if (i < numOfMusic)
		return music[i];
	else
		return nullptr;
}

void ResourceManager::setSoundEffects(std::vector<std::string> soundEffectsVect) {
	closeSoundEffects();
	numOfSoundEffects = soundEffectsVect.size();
	soundEffects = new SoundEffect*[numOfSoundEffects];
	for (int i = 0; i < numOfSoundEffects; i++) {
		soundEffects[i] = new SoundEffect(soundEffectsVect[i]);
	}
}


void ResourceManager::closeSoundEffects() {
	for (int i = 0; i < numOfSoundEffects; i++) {
		if (soundEffects[i] != nullptr) {
			delete soundEffects[i];
		}
	}
	delete[] soundEffects;
	numOfSoundEffects = 0;
}

SoundEffect*  ResourceManager::getSoundEffect(SoundEffectId i) const {
	if (i < numOfSoundEffects)
		return soundEffects[i];
	else
		return nullptr;
}