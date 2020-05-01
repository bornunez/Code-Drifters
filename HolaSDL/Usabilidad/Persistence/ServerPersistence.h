#pragma once
#include "IPersistence.h"
#include "../concurrentqueue.h"
#include "../../Timer.h"
#include <thread>

class ServerPersistence :
	public IPersistence
{
private:
	float flushTime = 30;
	atomic<bool> exit = false;
	Timer* timer;
	moodycamel::ConcurrentQueue<TrackerEvent*> eventQueue;		//Cola concurrente para poder añadir eventos de manera asincrona entre dos o mas hebras
	std::thread flushThread;

	void SendToServer(string s);
	void AsynFlush();

public:

	ServerPersistence(ISerializer* serializer, float flushTime);

	void Init();
	void End();

	//Metodo usado para encolar un evento al sistema de persistencia
	virtual void Send(TrackerEvent* e);

	//Metodo usado para enviar los eventos almacenados al servidor donde se registran
	virtual void Flush();

};

