#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Renderer.h"
struct TTF_font;

namespace piMath {
	

	class Font {
	public:
		Font() = default;
		~Font();

		bool Load(const std::string& name, float fontSize);

	private:
		friend class Text;
		TTF_Font* m_ttfFont{ nullptr };
	};
};