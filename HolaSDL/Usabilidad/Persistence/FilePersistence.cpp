#include "FilePersistence.h"
#include <filesystem> // or #include <filesystem>


#include <iostream>
#include <windows.h>
#include <stdio.h>

using namespace std;



void CreateFolder(const char* path)
{
	if (!CreateDirectory(path, NULL))
	{
		return;
	}
}


void FilePersistence::Init()
{

	CreateFolder("../Tracker");


	file.open(path);

	if (!file.is_open())
		cout << "Error abriendo el archivo " << path << endl;
}

void FilePersistence::End()
{
	if (file.is_open())
		file.close();
}

void FilePersistence::Send(TrackerEvent* e)
{
	if (file.is_open()) {
		string s = serializer->Serialize(e);
		cout << s << endl;
		file << s <<endl;
	}
}

void FilePersistence::Flush()
{

}
