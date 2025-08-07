#include "Texture.h"
#include "Math/Vector2.h"
namespace piMath {

	Texture::~Texture()
	{
		if (!m_texture) SDL_DestroyTexture(m_texture);
	}

	bool Texture::Load(const std::string& filename, Renderer& renderer)
	{
		SDL_Surface* surface = IMG_Load(filename.c_str());

		if (!surface)
		{
			std::cerr << "Could not load image: " << filename << std::endl;
			return false;
		}

		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		// once texture is created, surface can be freed up
		SDL_DestroySurface(surface);
		if (!m_texture)
		{
			std::cerr << "Could not create texture: " << filename << std::endl;
			return false;
		}

		return true;
	}

	vec2 Texture::GetSize()
	{
		float w,h;
		SDL_GetTextureSize(m_texture, &w, &h);

		return { w,h };
	}

}

