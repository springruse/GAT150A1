#pragma once
#include "../Math/Vector2.h"
#include <vector>
#include <array>


namespace piMath {

	class InputSystem {

	public:
		InputSystem() = default;
		bool Initialize();
		void Shutdown();
		void Update();

		// Key Inputs

		bool getKeyDown(uint8_t key) const { return m_keyboardState[key]; }
		bool getPreviousKeyDown(uint8_t key) const { return m_previousKeyboardState[key]; }
		bool getKeyPressed(uint8_t key) const { return !m_previousKeyboardState[key] && m_keyboardState[key]; }
		bool getKeyReleased(uint8_t key) const { return m_previousKeyboardState[key] && !m_keyboardState[key]; }

		// Mouse Inputs
		bool getMouseButtonDown(uint8_t button) { assert(button < 3); return m_mouseButtonState[button]; }
		bool getPreviousMouseButtonDown(uint8_t button) { assert(button < 3); return m_previousMouseButtonState[button]; }
		bool GetMousePressed(uint8_t button) { assert(button < 3); return !m_previousMouseButtonState[button] && m_mouseButtonState[button]; }
		bool GetMouseReleased(uint8_t button) { assert(button < 3); return m_previousMouseButtonState[button] && !m_mouseButtonState[button]; }

		const vec2& getMousePosition() const { return m_mousePosition; }
		const vec2& getPreviousMousePosition() const { return m_previousMousePosition; }

	private:
		std::vector<bool> m_keyboardState;
		std::vector<bool> m_previousKeyboardState;

		piMath::vec2 m_mousePosition{0,0};
		piMath::vec2 m_previousMousePosition{0,0};

		std::array<bool, 3> m_mouseButtonState{ false,false,false };
		std::array<bool, 3> m_previousMouseButtonState{ false,false,false };
	};
}