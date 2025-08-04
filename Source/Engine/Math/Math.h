#pragma once
#include <algorithm>
#include <cmath>

namespace piMath::Math {
	
	constexpr float pi = 3.14159265358979323846f; // Pi constant
	constexpr float two_pi = 6.28318530717958647692f; // 2 * Pi constant
	constexpr float half_pi = 1.57079632679489661923f; // Pi / 2 constant

	/// <summary>
	/// Converts an angle from radians to degrees.
	/// </summary>
	/// <param name="radius">The angle in radians to convert.</param>
	/// <returns>The angle converted to degrees.</returns>
	constexpr float radToDeg(float radius) {
		return radius * (180.0f / pi);
	}
	/// <summary>
	/// Converts an angle from degrees to radians.
	/// </summary>
	/// <param name="degrees">The angle in degrees to convert.</param>
	/// <returns>The angle in radians.</returns>
	constexpr float degToRad(float degrees) {
		return degrees * (pi / 180.0f);
	}
	/// <summary>
	/// Wraps an integer value within a specified range [min, max), cycling around if necessary.
	/// </summary>
	/// <param name="value">The integer value to wrap.</param>
	/// <param name="min">The inclusive lower bound of the range.</param>
	/// <param name="max">The exclusive upper bound of the range.</param>
	/// <returns>The wrapped integer value within the range [min, max).</returns>
	constexpr int Wrap(int value, int min, int max) {
		int range = max - min;
		int result = (value - min) % range;
		if (result < 0) result += range;
		return min + result;
	}
	/// <summary>
	/// Wraps a floating-point value into the range [min, max) using modular arithmetic.
	/// </summary>
	/// <param name="value">The value to wrap within the specified range.</param>
	/// <param name="min">The lower bound of the range.</param>
	/// <param name="max">The upper bound of the range (exclusive).</param>
	/// <returns>The wrapped value, guaranteed to be within [min, max).</returns>
	inline float Wrap(float value, float min, float max) {
		float range = max - min;
		float result = std::fmodf(value - min, range);
		if (result < 0) result += range;
		return min + result;
	}
	template<typename t>
	inline t Sign(t v) {
		return (v < 0) ? (t)-1 : (v > 0) ? (t)1 : (t)0; // if less than 0 return -1, else bigger than 0 return 1, and if both fail, move to 0
	}

	using std::min;
	using std::max;
	using std::clamp;
	using std::sqrt;
	using std::sqrtf;
	using std::sin;
	using std::sinf;
	using std::cos;
	using std::acosf;
	using std::cosf;
	using std::tan;
	using std::tanf;
	using std::atan2;
	using std::atan2f;
	using std::abs;

	// namespace Math above
}