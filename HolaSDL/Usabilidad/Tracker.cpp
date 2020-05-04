#include "Tracker.h"

Tracker* Tracker::instance = nullptr;

void Tracker::SetSerializer()
{
	switch (serializerType)
	{
	case JSON:
		serializerObject = new JSONSerializer();
		break;
	case XML:
		serializerObject = new XMLSerializer();
		break;
	default:
		break;
	}
}

void Tracker::SetPersistance()
{
	switch (persistenceType)
	{
	case FILE_PERSISTANCE:
		persistenceObject = new FilePersistence(serializerObject, "../Tracker/" + GAME_ID + ".log");
		break;
	case SERVER_PERSISTANCE:
		persistenceObject = new ServerPersistence(serializerObject, SERVER_FLUSH_TIME);
		break;
	}
}

std::time_t Tracker::getTime()
{
	return std::time(nullptr);
}

string Tracker::getDateString()
{
	auto t = std::time(nullptr);
	struct tm buf;
	localtime_s(&buf, &t);

	std::ostringstream oss;
	oss << std::put_time(&buf, "%d-%m-%Y %H-%M-%S");
	return oss.str();
}

string Tracker::getTimeString()
{
	auto t = std::time(nullptr);
	struct tm buf;
	localtime_s(&buf, &t);

	std::ostringstream oss;
	oss << std::put_time(&buf, "%H:%M:%S");
	return oss.str();

}

void Tracker::Init(string machineID)
{
	GAME_ID = machineID+"_"+getDateString();
	
	//Primero creamos las cosas en funcion de las opciones
	SetSerializer();
	SetPersistance();

	persistenceObject->Init();
	std::cout << "Game ID: " << GAME_ID << std::endl;
}

void Tracker::End()
{
	persistenceObject->End();

	delete persistenceObject;
	delete serializerObject;
}

void Tracker::TrackEvent(TrackerEvent* e)
{
	persistenceObject->Send(e);
}

TrackerEvent* Tracker::GenerateTrackerEvent(EventType type)
{
	TrackerEvent* e = new TrackerEvent(getTime(), type);
	return e;
}

AttackEvent* Tracker::GenerateAtackEvent(ATTACK_TYPE type)
{
	AttackEvent* e = new AttackEvent(getTime(), type);
	return e;
}

ComboEvent* Tracker::GenerateComboEvent(COMBO_TYPE type)
{
	ComboEvent* e = new ComboEvent(getTime(), type);
	return e;
}

LevelEvent* Tracker::GenerateLevelEvent(LEVEL_EVENT_TYPE type, int levelNum)
{
	LevelEvent* e = new LevelEvent(getTime(), type, levelNum);
	return e;
}

Tracker* Tracker::getInstance()
{
	if (instance == nullptr)
		instance = new Tracker();
	return instance;
}
