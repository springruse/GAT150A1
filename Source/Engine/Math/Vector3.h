#pragma once
#include <cassert>
#include <iostream>
#include "Math.h"

namespace claw {
	template<typename T>
	struct Vector3
	{
		union {
			struct { T x, y, z; };
			struct { T r, g, b; };

		};


		Vector3() = default;
		Vector3(T x, T y, T z) : x(x), y(y) , z(z){};

		T operator [] (unsigned int index) const { assert(index < 3);  return (&x)[index]; }
		T& operator [] (unsigned int index) { assert(index < 3);  return (&x)[index]; }

		Vector3 operator +(const Vector3& v) const // positive
		{
			return Vector3{ x + v.x, y + v.y, z + v.y };
		}
		Vector3 operator -(const Vector3& v) const // negative
		{
			return Vector3{ x - v.x, y - v.y, z - v.y };
		}
		Vector3 operator *(const Vector3& v) const // mult
		{
			return Vector3{ x * v.x, y * v.y, z * v.y };
		}
		Vector3 operator /(const Vector3& v) const // divide
		{
			return Vector3{ x / v.x, y / v.y, z / v.y };
		}

		// Comparison operators
		Vector3 operator +(float s) const { return Vector3{ x + s, y + s, z + s }; }
		Vector3 operator -(float s) const { return Vector3{ x - s, y - s, z - s }; }
		Vector3 operator *(float s) const { return Vector3{ x * s, y * s, z * s }; }
		Vector3 operator /(float s) const { return Vector3{ x / s, y / s, z / s }; }

		Vector3& operator += (float s) { x += s; y += s; z += s; return *this; }
		Vector3& operator -= (float s) { x -= s; y -= s; z -= s; return *this; }
		Vector3& operator *= (float s) { x *= s; y *= s; z *= s; return *this; }
		Vector3& operator /= (float s) { x /= s; y /= s; z /= s;return *this; }

		Vector3& operator += (const Vector3& v) { x += v.x; y += v.y; z += v.y; return *this; }
		Vector3& operator -= (const Vector3& v) { x -= v.x; y -= v.y; z -= v.y; return *this; }
		Vector3& operator *= (const Vector3& v) { x *= v.x; y *= v.y; z *= v.y; return *this; }
		Vector3& operator /= (const Vector3& v) { x /= v.x; y /= v.y; z /= v.y; return *this; }

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

	};

	template<typename T>
	std::ostream& operator << (std::ostream& stream, const Vector3<T>& v) {
		stream << "{" << v.x << ", " << v.y << ", " << v.z << "}";
		return stream;
	}

	template<typename T>
	std::istream& operator >> (std::istream& stream, Vector3<T>& v) {
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
		if (!(stream >> std::ws >> ch || ch != ',')) {
			stream.setstate(std::ios::failbit);
			return stream;
		} // skip comma
		if (!(stream >> std::ws >> v.z)) {
			stream.setstate(std::ios::failbit);
			return stream;
		} // read z value
		if (!(stream >> std::ws >> ch || ch != '}')) {
			stream.setstate(std::ios::failbit);
			return stream;
		} // skip closing brace

		return stream;
	}
	using ivec3 = Vector3<int>;
	using vec3 = Vector3<float>;
}