#pragma once
class Tracker
{
	static Tracker* instance;



public:

	static Tracker* getInstance() {
		if (instance == nullptr)
			instance = new Tracker();
		return instance;
	}
};

