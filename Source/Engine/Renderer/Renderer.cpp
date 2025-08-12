#include "Renderer.h"

bool piMath::Renderer::Initialize()
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
		Logger::Error("SDL_Init Error: " , std::string(SDL_GetError()));
        return false;
    }

    if (!TTF_Init()) {
		Logger::Error("TTF_Init Error: " , std::string(SDL_GetError()));
        return false;
    }

    return true;
}

void piMath::Renderer::Shutdown()
{
    TTF_Quit();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool piMath::Renderer::CreateWindow(const std::string& name, int width, int height)
{
	m_width = width;
	m_height = height;
    m_window = SDL_CreateWindow(name.c_str(), width, height, 0);
    if (m_window == nullptr) {
		Logger::Error("SDL_CreateWindow Error: " );
        SDL_Quit();
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, NULL);
    if (m_renderer == nullptr) {
		Logger::Error("SDL_CreateRenderer Error: " );
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    return true;
}

void piMath::Renderer::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
}

void piMath::Renderer::SetColor(float r, float g, float b, float a)
{
    SDL_SetRenderDrawColorFloat(m_renderer, r, g, b, a);
}

void piMath::Renderer::DrawLine(float x1, float y1, float x2, float y2)
{
    SDL_RenderLine(m_renderer, x1, y1, x2, y2);
}

void piMath::Renderer::DrawPoint(float x, float y)
{
    SDL_RenderPoint(m_renderer, x, y);
}

void piMath::Renderer::DrawTexture(Texture& texture, float x, float y)
{

    vec2 size = texture.GetSize();

        SDL_FRect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = size.x;
    destRect.h = size.y;

    SDL_RenderTexture(m_renderer, texture.m_texture, NULL, &destRect);
}

void piMath::Renderer::DrawTexture(Texture& texture, float x, float y, float scale, float angle)
{

    vec2 size = texture.GetSize();

    SDL_FRect destRect;
    destRect.w = size.x * scale;
    destRect.h = size.y * scale;
    destRect.x = x - destRect.w * 0.5f;
    destRect.y = y - destRect.h * 0.5f;

    SDL_RenderTextureRotated(m_renderer, texture.m_texture, NULL, &destRect, angle, NULL, SDL_FLIP_NONE());
}

void piMath::Renderer::Clear()
{
    SDL_RenderClear(m_renderer);
}

void piMath::Renderer::Present()
{
    SDL_RenderPresent(m_renderer);
}
