#pragma once
#include "Math.h"
#include <cassert>
#include <iostream>

namespace claw {
	template<typename T>
	struct Vector2
	{

		union {
			struct { T x, y; };
			struct { T x, y; };
		};

		Vector2() = default;
		Vector2(T x, T y) : x(x), y(y) {};

		T operator [] (unsigned int index) const { assert(index < 2);  return (&x)[index]; }
		T& operator [] (unsigned int index) { assert(index < 2);  return (&x)[index]; }

		Vector2 operator +(const Vector2& v) const // positive
		{
			return Vector2{ x + v.x, y + v.y };
		}
		Vector2 operator -(const Vector2& v) const // negative
		{
			return Vector2{ x - v.x, y - v.y };
		}
		Vector2 operator *(const Vector2& v) const // mult
		{
			return Vector2{ x * v.x, y * v.y };
		}
		Vector2 operator /(const Vector2& v) const // divide
		{
			return Vector2{ x / v.x, y / v.y };
		}

		// Comparison operators
		Vector2 operator +(float s) const { return Vector2{ x + s, y + s }; }
		Vector2 operator -(float s) const { return Vector2{ x - s, y - s }; }
		Vector2 operator *(float s) const { return Vector2{ x * s, y * s }; }
		Vector2 operator /(float s) const { return Vector2{ x / s, y / s }; }

		Vector2& operator += (float s) { x += s; y += s; return *this; }
		Vector2& operator -= (float s) { x -= s; y -= s; return *this; }
		Vector2& operator *= (float s) { x *= s; y *= s; return *this; }
		Vector2& operator /= (float s) { x /= s; y /= s; return *this; }

		Vector2& operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
		Vector2& operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; }
		Vector2& operator *= (const Vector2& v) { x *= v.x; y *= v.y; return *this; }
		Vector2& operator /= (const Vector2& v) { x /= v.x; y /= v.y; return *this; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		float LengthSqr() const{
			return (x * x) + (y * y);
		}
		float Length() const{
			return claw::Math::sqrtf(LengthSqr());
		}
		/// <summary>
		/// returns a normalized unit length version of the vector
		/// </summary>
		/// <returns></returns>
		Vector2 Normalize() const {
			return *this / Length();
		}

		/// <summary>
		/// calculate angle in radians between positive x-axis and the point
		/// </summary>
		/// <returns></returns>
		float Angle() const { return Math::atan2f(y, x); };

		Vector2 Rotate(float radians) const {
			Vector2 v;
			v.x = x * Math::cosf(radians) - y * Math::sinf(radians);
			v.y = x * Math::sinf(radians) + y * Math::cosf(radians);
			return v;
		};

		/// <summary>
		/// Calculates the dot product of two 2D vectors.
		/// </summary>
		/// <param name="a">The first 2D vector.</param>
		/// <param name="b">The second 2D vector.</param>
		/// <returns>The dot product of the two vectors as a float.</returns>
		static float Dot(const Vector2& a, const Vector2& b) {
			return a.x * b.x + a.y * b.y;
		}
		/// <summary>
		/// Calculates the angle in radians between two 2D vectors.
		/// </summary>
		/// <param name="a">The first 2D vector.</param>
		/// <param name="b">The second 2D vector.</param>
		/// <returns>The angle in radians between vectors a and b.</returns>
		static float AngleBetween(const Vector2& a, const Vector2& b) {
			return Math::acosf(Dot(a,b));
		}

		/// <summary>
		/// Calculates the signed angle in radians between two 2D vectors.
		/// </summary>
		/// <param name="a">The first 2D vector.</param>
		/// <param name="b">The second 2D vector.</param>
		/// <returns>The signed angle in radians from vector 'a' to vector 'b'. The sign indicates the direction of rotation.</returns>
		static float SignedAngleBetween(const Vector2& a, const Vector2& b) {
			Vector2 v{ Dot(a,b) , Cross(a,b) };
			return v.Angle();
		}

		/// <summary>
		/// Computes the 2D cross product (scalar) of two vectors.
		/// </summary>
		/// <param name="a">The first 2D vector operand.</param>
		/// <param name="b">The second 2D vector operand.</param>
		/// <returns>The scalar value representing the magnitude of the 2D cross product of vectors a and b.</returns>
		static float Cross(const Vector2& a, const Vector2& b) {
			return a.x * b.y - a.y * b.x;
		}
	};
	template<typename T>
	std::ostream& operator << (std::ostream& stream, const Vector2<T>& v) {
		stream << "{" << v.x << ", " << v.y << "}";
		return stream;
	}
	template<typename T>
	std::istream& operator >> (std::istream& stream, Vector2<T>& v) {
		char ch = '\0';
		if (!(stream >> std::ws >> ch || ch != '{')) {
			stream.setstate(std::ios::failbit);
			return stream;
		} // skip opening brace 
		if (!(stream >> std::ws >> v.x)) { 
			stream.setstate(std::ios::failbit);
			return stream; 
		} // read x value
		if (!(stream >> std::ws >> ch || ch != ',')) { 
			stream.setstate(std::ios::failbit);
			return stream; 
		} // skip comma
		if (!(stream >> std::ws >> v.y)) {
			stream.setstate(std::ios::failbit);
			return stream;
		} // read y value
		if (!(stream >> std::ws >> ch || ch != '}')) {
			stream.setstate(std::ios::failbit);
			return stream;
		} // skip closing brace

		return stream;
	}
	using ivec2 = Vector2<int>;
	using vec2 = Vector2<float>;
}