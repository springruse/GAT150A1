#pragma once


namespace piMath {
	template<typename T>
	struct Vector2 
	{
		T x, y;

		Vector2() = default;
		Vector2(T x, T y) : x(x), y(y) {};
	};

	using ivec2 = Vector2<int>;
	using vec2 = Vector2<float>;

}