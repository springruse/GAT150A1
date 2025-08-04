#pragma once
#include "Vector2.h"
#include "Vector3.h"

namespace piMath{
	struct Transform {
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
	};
}