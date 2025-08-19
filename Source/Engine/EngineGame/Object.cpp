#include "EnginePCH.h"
namespace claw {
	void claw::Object::Read(const json::value_t& value)
	{
		JSON_READ(value, name);
		JSON_READ(value, active);
	}
}
