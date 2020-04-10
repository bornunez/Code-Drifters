#pragma once
#include "IPersistence.h"
#include <fstream>

class FilePersistence : public IPersistence
{
private:
	
	string path;			//Ruta del fichero de volcado (En un principio es la ID de sesion)
	ofstream file;			//Archivo de volcado

public:

	FilePersistence(string path) : path(path) {	}

	void Init();
	void End();

	virtual void Send(TrackerEvent e);
	virtual void Flush();
};

