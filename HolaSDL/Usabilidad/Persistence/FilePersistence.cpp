#include "FilePersistence.h"

#include <iostream>

using namespace std;

void FilePersistence::Init()
{
	file.open(path);

	if (!file.is_open())
		cout << "Error abriendo el archivo " << path << endl;
}

void FilePersistence::End()
{
	if (file.is_open())
		file.close();
}

void FilePersistence::Send(TrackerEvent e)
{
	if (file.is_open()) {
		file << serializer->Serialize(e) <<endl;
	}
}

void FilePersistence::Flush()
{

}
