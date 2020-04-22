#pragma once

#include "Event/TrackerEvent.h"
#include "Persistence/IPersistence.h"
#include "Serializer/ISerializer.h"
#include "Serializer/JSONSerializer.h"
#include "Persistence/FilePersistence.h"
#include "Event/AttackEvent.h"
#include "Event/ComboEvent.h"
#include "Event/LevelEvent.h"
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

class Tracker
{
private:
	static Tracker* instance;

	IPersistence* persistenceObject;
	ISerializer* serializerObject;
 	string GAME_ID = "";


	static std::time_t getTime() {
		return std::time(nullptr);
	}
	string getDateString() {
		auto t = std::time(nullptr);
		struct tm buf;
		localtime_s(&buf,&t);

		std::ostringstream oss;
		oss << std::put_time(&buf, "%d-%m-%Y %H-%M-%S");
		return oss.str();

	}
	string getTimeString() {
		auto t = std::time(nullptr);
		struct tm buf;
		localtime_s(&buf, &t);

		std::ostringstream oss;
		oss << std::put_time(&buf, "%H:%M:%S");
		return oss.str();

	}

public:

	Tracker() {

	}

	void Init() {
		serializerObject = new JSONSerializer();
		GAME_ID = getDateString();
		
		persistenceObject = new FilePersistence(serializerObject, "../Tracker/" + GAME_ID + ".log");
		persistenceObject->Init();
		std::cout << "Game ID: " << GAME_ID << std::endl;
	}
	void End() {
		persistenceObject->End();

		delete persistenceObject;
		delete serializerObject;
	}
	void TrackEvent(TrackerEvent* e) {
		persistenceObject->Send(e);
		delete e;
	}
	static TrackerEvent* GenerateTrackerEvent(EventType type) {
		TrackerEvent* e = new TrackerEvent(getTime(), type);
		return e;
	}
	static AttackEvent* GenerateAtackEvent(ATTACK_TYPE type) {
		AttackEvent* e = new AttackEvent(getTime(), type);
		return e;
	}
	static ComboEvent* GenerateComboEvent(COMBO_TYPE type) {
		ComboEvent* e = new ComboEvent(getTime(), type);
		return e;
	}
	static LevelEvent* GenerateLevelEvent(LEVEL_EVENT_TYPE type,int levelNum) {
		LevelEvent* e = new LevelEvent(getTime(), type, levelNum);
		return e;
	}

	static Tracker* getInstance() {
		if (instance == nullptr)
			instance = new Tracker();
		return instance;
	}
};

