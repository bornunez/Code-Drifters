#include "ServerPersistence.h"

void ServerPersistence::SendToServer(string s)
{
	cout << "Sending to server... [ " + s + " ]" << endl;
}

void ServerPersistence::AsynFlush()
{
	//Mientras este el juego activo vamos a estar mandando informacion al servidor cada X tiempo.
	while (!exit)
	{
		timer->update();
		//Si es hora de mandar los datos al servidor, los mandamos y limpiamos la cola
		if (timer->TimeSinceTimerCreation > flushTime) {
			timer->restart();
			Flush();

		}
	}
}

ServerPersistence::ServerPersistence(ISerializer* serializer, float flushTime) : IPersistence(serializer), flushThread(), flushTime(flushTime)
{
	timer = new Timer();
}

void ServerPersistence::Init()
{
	//Reseteamos el timer por seguridad
	timer->restart(); 
	//Y lanzamos el hilo
	flushThread = std::thread(&ServerPersistence::AsynFlush, this);		
}

void ServerPersistence::End()
{
	exit = true;
	flushThread.join();
}

void ServerPersistence::Send(TrackerEvent* e)
{
	eventQueue.enqueue(e);
	cout << "Encolando evento [ " << serializer->Serialize(e) << " ] " << endl;
}

void ServerPersistence::Flush()
{
	cout << "Enviando datos...." << endl;
	TrackerEvent* e;

	//Sacamos los eventos que hubiera en el momento de la llamada, los serializamos y los mandamos al servidor
	while (eventQueue.try_dequeue(e))
	{
		string event = serializer->Serialize(e);
		SendToServer(event);
		delete e;
	}
}
