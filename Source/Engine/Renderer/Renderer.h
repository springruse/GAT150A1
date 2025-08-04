#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include <SDL3_ttf/SDL_ttf.h>
namespace piMath {

	class Renderer
	{
	public:
		Renderer() = default;
		bool Initialize();
		void Shutdown();
		bool CreateWindow(const std::string& name, int width, int height);

		void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		void SetColor(float r, float g, float b, float a = 1.0);


		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawPoint(float x, float y);

		void Clear();
		void Present();

		int getWidth() const { return m_width; }
		int getHeight() const { return m_height; }

	private:
		int m_width = { 0 };
		int m_height = { 0 };
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;
		friend class Text;
	};

}

