#pragma once
#include <cstdlib>
#include <random>
#include "Math/Vector2.h"
#include "Math.h"

namespace piMath {
	namespace Random {
		/// <summary>
		/// Returns a reference to a static Mersenne Twister random number generator instance.
		/// </summary>
		/// <returns>A reference to a static std::mt19937 random number generator.</returns>
		inline std::mt19937& generator() {
			static std::random_device rd;
			static std::mt19937 gen(rd());
			return gen;
		}
		/// <summary>
		/// Seeds the random number generator with the specified value.
		/// </summary>
		/// <param name="value">The seed value to initialize the random number generator.</param>
		inline void seed(unsigned int value) {
			generator().seed(value);
		}
		/// <summary>
		/// Generates a random integer within the specified range, inclusive.
		/// </summary>
		/// <param name="min">The minimum value of the range (inclusive).</param>
		/// <param name="max">The maximum value of the range (inclusive).</param>
		/// <returns>A randomly generated integer between min and max, inclusive.</returns>
		inline int getInt(int min, int max) {
			std::uniform_int_distribution<> dist(min, max);
			return dist(generator());
		}
		/// <summary>
		/// Returns a random integer in the range [0, max - 1].
		/// </summary>
		/// <param name="max">The exclusive upper bound for the random integer.</param>
		/// <returns>A random integer greater than or equal to 0 and less than max.</returns>
		inline int getInt(int max) {
			return getInt(0, max - 1);
		}
		/// <summary>
		/// Generates a random integer using a static uniform integer distribution and a generator.
		/// </summary>
		/// <returns>A randomly generated integer.</returns>
		inline int getInt() {
			static std::uniform_int_distribution<> dist;
			return dist(generator());
		}
		/// <summary>
		/// Generates a random real number within the specified range [min, max).
		/// </summary>
		/// <typeparam name="T">The floating-point type to use for the random number (defaults to float).</typeparam>
		/// <param name="min">The inclusive lower bound of the range.</param>
		/// <param name="max">The exclusive upper bound of the range.</param>
		/// <returns>A random real number of type T in the range [min, max).</returns>
		template <typename T = float>
		inline T getReal(T min, T max) {
			std::uniform_real_distribution<T> dist(min, max);
			return dist(generator());
		}
		/// <summary>
		/// Generates a random real number in the range [0, max).
		/// </summary>
		/// <typeparam name="T">The floating-point type to use for the random number. Defaults to float.</typeparam>
		/// <param name="max">The exclusive upper bound for the generated random number.</param>
		/// <returns>A random real number of type T in the range [0, max).</returns>
		template <typename T = float>
		inline T getReal(T max) {
			return getReal(static_cast<T>(0), static_cast<T>(max));
		}
		/// <summary>
		/// Generates a random real number in the range [0, 1).
		/// </summary>
		/// <typeparam name="T">The floating-point type of the generated random number. Defaults to float.</typeparam>
		/// <returns>A random real number of type T in the range [0, 1).</returns>
		template <typename T = float>
		inline T getReal() {
			static std::uniform_real_distribution<T> dist(static_cast<T>(0), static_cast<T>(1));
			return dist(generator());
		}
		/// <summary>
		/// Generates a random boolean value with equal probability for true or false.
		/// </summary>
		/// <returns>A randomly generated boolean value (true or false) with a probability of 0.5 for each.</returns>
		inline bool getBool() {
			static std::bernoulli_distribution dist(0.5);
			return dist(generator());
		}
		/// <summary>
		/// Generates a random 2D unit vector lying on the unit circle.
		/// </summary>
		/// <returns>A vec2 representing a random point on the unit circle.</returns>
		inline vec2 onUnitCircle() {
			float radians = getReal(0.0f, Math::two_pi);
			vec2 v;
			v.x = Math::cosf(radians);
			v.y = Math::sinf(radians);
			return v;
		}
	}
}