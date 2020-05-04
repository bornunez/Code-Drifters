#pragma once

#include "Event/TrackerEvent.h"
#include "Persistence/IPersistence.h"
#include "Serializer/ISerializer.h"
#include "Serializer/JSONSerializer.h"
#include "Serializer/XMLSerializer.h"
#include "Persistence/FilePersistence.h"
#include "Persistence/ServerPersistence.h"
#include "Event/AttackEvent.h"
#include "Event/ComboEvent.h"
#include "Event/LevelEvent.h"
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;
enum PERSISTENCE_TYPE { FILE_PERSISTANCE, SERVER_PERSISTANCE };
enum SERIALIZER_TYPE { JSON, XML };

const float SERVER_FLUSH_TIME = 30; //Frecuencia con la que se envian los datos  al servidor (Molaria llevarlo a un JSON tambien)

class Tracker
{
private:
	static Tracker* instance;

	//Opciones del tracker (Molaria llevarlo a un JSON)
	PERSISTENCE_TYPE persistenceType = FILE_PERSISTANCE;
	SERIALIZER_TYPE serializerType = JSON;

	//Atributos del Tracker
	IPersistence* persistenceObject;
	ISerializer* serializerObject;
 	string GAME_ID = "";



	void SetSerializer();
	void SetPersistance();

	static std::time_t getTime();
	string getDateString();
	string getTimeString();

public:

	Tracker() {

	}

	void Init(string machineId);
	void End();
	void TrackEvent(TrackerEvent* e);
	static TrackerEvent* GenerateTrackerEvent(EventType type);
	static AttackEvent* GenerateAtackEvent(ATTACK_TYPE type);
	static ComboEvent* GenerateComboEvent(COMBO_TYPE type);
	static LevelEvent* GenerateLevelEvent(LEVEL_EVENT_TYPE type, int levelNum);

	static Tracker* getInstance();
};

