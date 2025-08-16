#include "Mesh.h"
#include "Renderer.h"
namespace claw {
	bool Mesh::Load(const std::string& filename)
	{
		std::string buffer;
		file::ReadTextFile(filename, buffer);
		std::stringstream stream(buffer);

		//// read the color
		//stream >> m_color;
		//vec2 point;

		//// read points
		//while (stream >> point) {
		//	m_points.push_back(point);
		//}

		if (!stream.eof()) {
			Logger::Error("Could not parse file: {}", filename);
		}

		return false;
	}
	void claw::Mesh::Draw(Renderer& renderer, const vec2& position, float scale, float rotation)
	{	
		renderer.SetColor(m_color.r, m_color.g, m_color.b);
		
		if (m_points.empty()) {
			return;
		}
		//iterate through all points and draw a line
		
		for (int i = 0; i < m_points.size() - 1; i++) {
			vec2 point1 = (m_points[i].Rotate(claw::Math::degToRad(rotation)) * scale) + position;
			vec2 point2 = (m_points[i + 1].Rotate(claw::Math::degToRad(rotation)) * scale) + position;

			renderer.DrawLine(point1.x, point1.y, point2.x, point2.y);
;		}
		
	}
	/// <summary>
	/// Draws the model using the specified renderer and transformation.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the model.</param>
	/// <param name="transform">The transformation to apply, including position, scale, and rotation.</param>
	void claw::Mesh::Draw(Renderer& renderer, const Transform& transform)
	{
		Draw(renderer, transform.position, transform.scale, transform.rotation);
	}

	void Mesh::CalculateRadius()
	{
		m_radius = 0.0f;
		for (auto& point : m_points) {
			float length = point.Length();
			if (length > m_radius) {
				m_radius = length;
			}
		}
	}

}

