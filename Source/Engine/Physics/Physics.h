#pragma once
#include <box2d/box2d.h>
#include <memory>

namespace claw {

	inline b2Vec2 to_b2(const vec2& v) {
		return b2Vec2{ v.x, v.y };
	}
	inline vec2 to_vec2(const b2Vec2& v) {
		return vec2{ v.x, v.y };
	}

	class Physics {
	public:
		Physics() = default;

		bool Initialize();
		void Shutdown();

		void Update(float dt);

		static vec2 WorldToPixel(const vec2& world) {
			return world * ms_pixelsPerUnit;
		}

		static vec2 PixelToWorld(const vec2& pixel) {
			return pixel / ms_pixelsPerUnit;
		}

		static void setPixelsPerUnit(float ppu) {
			ms_pixelsPerUnit = ppu;
		}

		void ProcessCollisionEvents();

		static float ms_pixelsPerUnit;
	private:
		friend class PhysicsBody;

		b2WorldId m_worldId;
	};
}	