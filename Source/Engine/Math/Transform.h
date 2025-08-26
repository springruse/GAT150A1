#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Core/Serializable.h"

namespace claw{
	struct Transform : public ISerializable{
		vec2 position = {0,0};
		float rotation = 0;
		float scale = 1;

		Transform() = default;
		Transform(const vec2& position, float rotation = 0, float scale = 1) :
			position{ position },
			rotation{ rotation },
			scale{ scale }
		{
		}

		// Implement the pure virtual function from Serializable
		void Read(const json::value_t& value) override;
	};
}