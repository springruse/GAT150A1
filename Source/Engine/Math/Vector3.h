#pragma once
#include <cassert>
#include "Math.h"

namespace piMath {
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
			return piMath::Math::sqrtf(LengthSqr());
		}

	};

	using ivec3 = Vector3<int>;
	using vec3 = Vector3<float>;
}