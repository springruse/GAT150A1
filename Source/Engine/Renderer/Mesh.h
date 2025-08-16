#pragma once
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Transform.h"
#include "../Resources/Resource.h"
#include <vector>

namespace claw {

	class Mesh : public Resource{
	public:
		Mesh() = default;
		Mesh(const std::vector<vec2> points, const vec3& color) :
			m_points{ points },
			m_color{ color }
		{
			CalculateRadius();
		};

		bool Load(const std::string& filename);

		void Draw(class Renderer& renderer, const vec2& position, float scale, float rotation);
		void Draw(class Renderer& renderer, const Transform& transform);

		float getRadius() const {
			return m_radius;
		}
	private:
		void CalculateRadius();

	private:
		float m_radius = 0.0f;
		std::vector<vec2> m_points;
		vec3 m_color{ 1,1,1 };
	};
}
