#pragma once
//#include "checkML.h"
#include "Texture.h"
#include <vector>
#include "Music.h"
#include "SoundEffect.h"

class Tileset;

// CONSTANTES
const int NUM_TEXTURES = 111;
const int NUM_TILESET = 1;
const int NUM_PROTATILESET = 2;
const int NUM_ENEMYTILESET = 8;
const int NUM_BOSS1TILESET = 1;
const int NUM_BOSS2TILESET = 1;
const int NUM_BOSS3TILESET = 1;
const string TEXT_PATH = "..\\images\\";
const string LEVEL_PATH = "..\\levels&tiles\\";
const string TILESET_PATH = "..\\levels&tiles\\";
const string ENEMY_PATH = "..\\Animations\\Enemies\\";
const string PROTATILESET_PATH = "..\\Animations\\Protagonist\\tileset\\";
const string BOSS1_PATH = "..\\Animations\\Bosses\\Boss1\\";
const string BOSS2_PATH = "..\\Animations\\Bosses\\Boss2\\";
const string BOSS3_PATH = "..\\Animations\\Bosses\\Boss3\\";
// Estructura para las texturas
typedef struct {
	string filename;
	int numRows;
	int numCols;
} TextureAtributes;

//Aqui se pone el nombre que se le va a dar  a la textura como argumento en el getTexture
enum TextureId {
	ImFin, MCBullet, MCGun, GunnerBullet, BombBullet, BossBullet, HookChain, HookChainFail, HookHead, Blood, GunnerBulletExplosion, StunParticle,
	
	//TIENDA
	Madam_P_Idle,
	Madam_P_Drinking,
	GirlSmoking,
	BlackLove,
	SafeSex,
	Stripper,
	Clients,

	//TEXTURAS DEL HUD
	LifeBarra, LifeBorde, LifeFondo, UltBorde, UltBarra, UltFondo, HUDBulletBarra, HUDBulletFondo, HUDBulletBorde,
	EnemyHUDBorde, EnemyHUDBarra, EnemyHUDFondo,
	LoadingScreenBG, LoadbarBarra,LoadBarFondo,

	PerroBorde, PerroBarra, PerroFondo, PerroSecondFill,
	BotonBorde, BotonBarra,

	//TEXTURAS DEL MINIMAPA
	MinimapBorder, MinimapBase, //Borde
	BaseRoom, //Todas las bases
	First_On,First_Off,Normal_On,Normal_Off,Boss_On,Boss_Off, Shop_On,Shop_Off, Chest_On,Chest_Off,
	//Todas las puertas abiertas
	OpenUp, OpenRight, OpenDown, OpenLeft,
	OpenUpNormalOn, OpenRightNormalOn, OpenDownNormalOn, OpenLeftNormalOn,
	OpenUpNormalOff, OpenRightNormalOff, OpenDownNormalOff, OpenLeftNormalOff,
	//Todas las puertas cerradas
	ClosedUp, ClosedRight, ClosedDown, ClosedLeft,

	//Props
	Burbujas1, Burbujas2, Burbujas3, Burbujas4, FetoIngeniero1, FetoIngeniero2, HologramaHaro, HologramaBase, HologramaWanted,
	Prop1, Prop2, Prop3, Prop4, Prop5, Prop6,

	OneCoinSprite, FiveCoinSprite,TenCoinSprite,
	BaseLifepack, HighLifepack,
	SwordButton, GunButton, MemexButton, MaxAttackButton, SwordChargeButton

	
};


// Music -- each file is loaded as an instance of Music
//
enum MusicId {
	Level1,
	Level2,
	Burdel,
	Dog,
	Button,
	FinalBoss1,
	FinalBoss2,
	SadEnd
};


// Sound Effects -- each file is loaded as an instance of SoundEffect
//
enum SoundEffectId {
	SoundEffect1,
	MCGunShot,
	MCSwordNormalAttack,
	EnemyStuned,
	HookThrow, HookHit, HookMiss,

	StalkerCharge, GunnerShot, ChargerCrash, BombSound,

	DogAttack1, DogAttack2,
	ButtonExplosion,
	SwordSlash
};

//IMPORTANTE//
//El orden en el que se ponen las cosas en la enum debe ser el mismo que en el que se añaden las cosas abajo en TextureAtributes ya que si no no van a coincidir

using namespace std;
class ResourceManager
{
private:
	//Aqui se añaden las texturas con estoso args {path, numRows, numCols}
	const TextureAtributes TEXTURE_ATRIBUTES[NUM_TEXTURES]{
		{ "ImFin.png", 1, 20 },
		{ "MCBullet.png", 1, 4 },
		{"GunRight.png",1,1},
		{ "GunnerBullet.png", 1, 5 },
		{ "BombBullet.png", 1, 5 },
		{ "BossBullet.png", 1, 4},
		{ "HookChain.png", 1,2},
		{"HookChainFail.png",2,13},
		{"HookHead.png", 1 ,2},
		{"Particles\\Blood.png", 3, 3},
		{ "Particles\\GunnerBulletExplosion.png", 2, 7 },
		{ "Particles\\StunParticle.png", 1, 7 },

		//Cosas de la tienda
		{"Puti\\Phernelia_Waiting.png",1,2},
		{ "Puti\\Phernelia_Drinking.png",1,2 },
		{"Puti\\ProstitutaSmokingLove.png",1,34},
		{ "Puti\\BlackLove1.png",1,3 },
		{ "Puti\\SafeSex.png",1,2 },
		{"Puti\\Stripper.png",1,17},
		{ "Puti\\clientes.png",1,24 },

		//HUD
		{"Interfaz\\Barra.png", 1, 1},
		{"Interfaz\\Borde.png", 1, 1},
		{"Interfaz\\Fondo.png",1,1},
		{"Interfaz\\BordeUlt.png", 1, 1},
		{"Interfaz\\BarraUlt.png",1, 1},
		{"Interfaz\\FondoUlt.png", 1, 1},
		{"Interfaz\\BalaBarra2.png", 1, 1},
		{"Interfaz\\BalaFondo2.png", 1, 1},
		{"Interfaz\\BalaBorde2.png", 1, 1},
		{"Interfaz\\EnemigoBorde.png", 1, 1},
		{"Interfaz\\EnemigoRelleno.png", 1, 1},
		{"Interfaz\\EnemigoFondo.png", 1, 1},

		{ "Interfaz\\Carga_Borde.png", 1, 1 },
		{ "Interfaz\\Carga_Barra.png", 1, 1 },
		{ "Interfaz\\Carga_Fondo.png", 1, 1 },


		//First Boss
		{"Interfaz\\PerroBorde.png", 1, 1},
		{"Interfaz\\PerroRelleno.png", 1, 1},
		{"Interfaz\\PerroBack.png", 1, 1},
		{"Interfaz\\PerroSegundoRelleno.png", 1, 1},
		//Second Boss
		{"Interfaz\\BotonBorde.png", 1, 1},
		{"Interfaz\\BotonRelleno.png", 1, 1},

		//MINIMAPA
		{"Interfaz\\Minimapa\\MinimapBorde.png",1,1},
		{ "Interfaz\\Minimapa\\MinimapBase.png",1,1 },
		{ "Interfaz\\Minimapa\\BaseRoom.png",1,1 },
		//Los rellenos
		{ "Interfaz\\Minimapa\\First_On.png",1,1 },
		{ "Interfaz\\Minimapa\\First_Off.png",1,1 },
		{ "Interfaz\\Minimapa\\Normal_On.png",1,1 },
		{ "Interfaz\\Minimapa\\Normal_Off.png",1,1 },
		{ "Interfaz\\Minimapa\\Boss_On.png",1,1 },
		{ "Interfaz\\Minimapa\\Boss_Off.png",1,1 },
		{ "Interfaz\\Minimapa\\Shop_On.png",1,1 },
		{ "Interfaz\\Minimapa\\Shop_Off.png",1,1 },
		{ "Interfaz\\Minimapa\\Chest_On.png",1,1 },
		{ "Interfaz\\Minimapa\\Chest_Off.png",1,1 },
		//Open
		{ "Interfaz\\Minimapa\\OpenUp.png",1,1 },
		{ "Interfaz\\Minimapa\\OpenRight.png",1,1 },
		{ "Interfaz\\Minimapa\\OpenDown.png",1,1 },
		{ "Interfaz\\Minimapa\\OpenLeft.png",1,1 },

		{ "Interfaz\\Minimapa\\OpenUpNormalOn.png",1,1 },
		{ "Interfaz\\Minimapa\\OpenRightNormalOn.png",1,1 },
		{ "Interfaz\\Minimapa\\OpenDownNormalOn.png",1,1 },
		{ "Interfaz\\Minimapa\\OpenLeftNormalOn.png",1,1 },

		{ "Interfaz\\Minimapa\\OpenUpNormalOff.png",1,1 },
		{ "Interfaz\\Minimapa\\OpenRightNormalOff.png",1,1 },
		{ "Interfaz\\Minimapa\\OpenDownNormalOff.png",1,1 },
		{ "Interfaz\\Minimapa\\OpenLeftNormalOff.png",1,1 },
		//Closed
		{ "Interfaz\\Minimapa\\ClosedUp.png",1,1 },
		{ "Interfaz\\Minimapa\\ClosedRight.png",1,1 },
		{ "Interfaz\\Minimapa\\ClosedDown.png",1,1 },
		{ "Interfaz\\Minimapa\\ClosedLeft.png",1,1 },
			//Props
		{ "Props\\burbujas1.png", 1, 6 },
		{ "Props\\burbujas2.png", 1, 6 },
		{ "Props\\burbujas3.png", 1, 6 },
		{ "Props\\burbujas4.png", 1, 6 },
		{ "Props\\EngineerFetus1.png", 1, 6 },
		{ "Props\\EngineerFetus2.png", 1, 6 },
		{ "Props\\HologramaHaro.png", 1, 8 },
		{ "Props\\HologramaBase.png", 1, 8 },
		{ "Props\\HologramaWanted.png", 1, 8 },
		{ "Props\\Prop1.png", 1, 8 },
		{ "Props\\Prop2.png", 1, 10 },
		{ "Props\\Prop3.png", 1, 2 },
		{ "Props\\Prop4.png", 1, 2 },
		{ "Props\\Prop5.png", 1, 10 },
		{ "Props\\Prop6.png", 1, 10 },

		{ "coin.png", 1, 4},
		{ "coin_five.png", 1, 4 },
		{ "coin_ten.png", 1, 4 },

		{"life.png",1,4},
		{"life_high.png",1,4 },

		{ "Tree\\1.png", 1, 1 },
		{ "Tree\\2.png", 1, 1 },
		{ "Tree\\3.png", 1, 1 },
		{ "Tree\\11.png", 1, 1 },
		{ "Tree\\12.png", 1, 1 },
		{ "Tree\\21.png", 1, 1 },
		{ "Tree\\22.png", 1, 1 },
		{ "Tree\\31.png", 1, 1 },
		{ "Tree\\32.png", 1, 1 },
		{ "Tree\\111.png", 1, 1 },
		{ "Tree\\121.png", 1, 1 },
		{ "Tree\\122.png", 1, 1 },
		{ "Tree\\211.png", 1, 1 },
		{ "Tree\\221.png", 1, 1 },
		{ "Tree\\311.png", 1, 1 },
		{ "Tree\\312.png", 1, 1 },
		{ "Tree\\321.png", 1, 1 },
		{ "Tree\\2211.png", 1, 1 },
		{ "Tree\\BlueLine.png", 1, 1 },
		{ "Tree\\GreenLine.png", 1, 1 },
		{ "Tree\\RedLine.png", 1, 1 },
		{ "Tree\\Line.png", 1, 1 },
		

		
	};

	//Sounds


	std::vector<std::string> ResourceManager::musicFiles{ 
		"..\\music\\Nivel1.wav",
		"..\\music\\Nivel2.wav",
		"..\\music\\Puticlub.wav",
		"..\\music\\PERR.wav",
		"..\\music\\Boton.wav",
		"..\\music\\BossFinal_Parte1.wav",
		"..\\music\\BossFinal_Parte2.wav",
		"..\\music\\SadEnd.wav"};

	std::vector<std::string> ResourceManager::soundEffectFiles{
		"..\\music\\Sonidos\cosa.wav",
		"..\\music\\Sonidos\\PistolaProta.wav",
		"..\\music\\Sonidos\\EspadaTest.wav",
		"..\\music\\Sonidos\\Stuned.wav",
		"..\\music\\Sonidos\\HookThrow.wav",
		"..\\music\\Sonidos\\HookHit.wav",
		"..\\music\\Sonidos\\HookMiss.wav",

		"..\\music\\Sonidos\\StalkerCharge.wav",
		"..\\music\\Sonidos\\GunnerShot.wav",
		"..\\music\\Sonidos\\ChargerCrash.wav",
		"..\\music\\Sonidos\\Bomb.wav",

		"..\\music\\Sonidos\\PerroRugido1.wav",
		"..\\music\\Sonidos\\PerroRugido2.wav",
	    "..\\music\\Sonidos\\BotonMuere.wav",
		"..\\music\\Sonidos\\SwordSlash.wav"};

	int numOfMusic;
	Music** music;

	int numOfSoundEffects;
	SoundEffect** soundEffects;

	//Array que contiene punteros a todas las texturas del juego.
	Texture* textures[NUM_TEXTURES];
	//Vector de tilesets
	vector<Tileset*> tilesets;
	const string protaTilesetName[NUM_PROTATILESET] = { "ProtaAnimation.tsx", "Ultimate.tsx" };
	vector<Tileset*> protaTileset;
	const string boss1TilesetNames[NUM_BOSS1TILESET]{ "Boss1.tsx" };
	const string boss2TilesetNames[NUM_BOSS2TILESET]{ "Boss2-Entero.tsx" };
	const string boss3TilesetNames[NUM_BOSS3TILESET]{ "Boss3.tsx" };
	const string enemyTilesetNames[NUM_ENEMYTILESET]
	{ 
		"Gunner.tsx", 
		"Stalker.tsx", 
		"Torreta.tsx", 
		"Charger.tsx" , 
		"Wheel.tsx",
		"Bomber.tsx",
		"Bomb.tsx",
		"Wave.tsx"
	};
	vector<Tileset*> enemyTilesets;
	vector<Tileset*> boss1Tilesets;
	vector<Tileset*> boss2Tilesets;
	vector<Tileset*> boss3Tilesets;


	SDL_Renderer* renderer;
	static ResourceManager* instance;

	void loadTextures();
	Tileset* loadTileset(string path);
	void loadProtaTileset();
	void loadEnemyTilesets();
	void loadBoss1Tilesets();
	void loadBoss2Tilesets();
	void loadBoss3Tilesets();

	//Music
	void setMusic(std::vector<std::string> musicVect);
	void closeMusic();
	void setSoundEffects(std::vector<std::string> soundEffectsVect);
	void closeSoundEffects();

	void closeTextures();
	void closeTilesets();
	//Constructor
	ResourceManager(SDL_Renderer* renderer);

public:
	static ResourceManager* getInstance() { return instance; }
	static void createInstance(SDL_Renderer* renderer);
	static void ResetInstance();

	~ResourceManager();

	//Devuelve la textura dado su numero en la enum
	Texture * getTexture(TextureId id);
	Tileset* getTileset(string path);
	Tileset* getProtaTileset(int numTileset) { return protaTileset[numTileset]; };
	Tileset* getEnemyTileset(int numTileset) { return enemyTilesets[numTileset]; };
	Tileset* getBoss1Tileset(int numTileset) { return boss1Tilesets[numTileset]; };
	Tileset* getBoss2Tileset(int numTileset) { return boss2Tilesets[numTileset]; };
	Tileset* getBoss3Tileset(int numTileset) { return boss3Tilesets[numTileset]; };
	string getLevelPath() { return LEVEL_PATH; };
	Music* getMusic(MusicId i) const;
	SoundEffect* getSoundEffect(SoundEffectId i) const;
	void muteMusic();
	void unmuteMusic();
	void muteSoundEffect();
	void unmuteSoundEffect();
};