#pragma once
#include "Font.h"
#include "Renderer.h"
#include "../Math/Math.h"
#include "../Math/Vector3.h"
#include <memory>
#include <string>

struct SDL_Texture;
namespace piMath {

	class Text {
	public:
		Text() = default;
		Text(std::shared_ptr<Font> font) : m_font{ font } {}
		~Text();

		bool Create(Renderer& Renderer, const std::string& text, const vec3& color);
		void Draw(Renderer& renderer, float x, float y);


	private:
		std::shared_ptr<class Font> m_font{ nullptr };
		SDL_Texture* m_texture{ nullptr };
		friend class Renderer;
	};
}
