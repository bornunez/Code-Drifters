#pragma once

#include "Event/TrackerEvent.h"
#include "Persistence/IPersistence.h"
#include "Serializer/ISerializer.h"
#include "Serializer/JSONSerializer.h"
#include "Persistence/FilePersistence.h"
#include "Event/AttackEvent.h"
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
	string getTimeString() {
		auto t = std::time(nullptr);
		struct tm buf;
		localtime_s(&buf,&t);

		std::ostringstream oss;
		oss << std::put_time(&buf, "%d-%m-%Y %H-%M-%S");
		return oss.str();

	}

public:

	Tracker() {

	}

	void Init() {
		serializerObject = new JSONSerializer();
		GAME_ID = getTimeString();
		
		persistenceObject = new FilePersistence(serializerObject, "../Tracker/" + GAME_ID + ".log");
		persistenceObject->Init();
		std::cout << "Game ID: " << GAME_ID << std::endl;
	}
	void End() {
		persistenceObject->End();

		delete persistenceObject;
		delete serializerObject;
	}
	void TrackEvent(TrackerEvent e) {
		persistenceObject->Send(e);
	}
	static AttackEvent Attack(ATTACK_TYPE type) {
		AttackEvent e(getTime(), type);
		return e;
	}

	static Tracker* getInstance() {
		if (instance == nullptr)
			instance = new Tracker();
		return instance;
	}
};

