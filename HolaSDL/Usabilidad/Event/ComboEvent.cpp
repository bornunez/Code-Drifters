#include "ComboEvent.h"

json ComboEvent::ToJson()
{

	jo["COMBO_TYPE"] = comboString[type];

	TrackerEvent::ToJson();
	return jo;
}
