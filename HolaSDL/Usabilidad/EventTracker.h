#pragma once
class EventTracker
{
	static EventTracker* instance;



public:

	static EventTracker* getInstance() {
		if (instance == nullptr)
			instance = new EventTracker();
		return instance;
	}
};

