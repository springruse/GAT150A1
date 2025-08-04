#include "InputSystem.h"
#include <SDL3/SDL.h>

namespace piMath {
	bool InputSystem::Initialize()
	{
		int numKeys;
		const bool* keyboardState = SDL_GetKeyboardState(&numKeys);
		m_keyboardState.resize(numKeys);
		std::copy(keyboardState, keyboardState + numKeys, m_keyboardState.begin());
		m_previousKeyboardState = m_keyboardState;

		SDL_GetMouseState(&m_mousePosition.x, &m_mousePosition.y);
		m_previousMousePosition = m_mousePosition;
		

		return true;
	}
	void InputSystem::Shutdown()
	{
		// nothing 
	}
	void InputSystem::Update()
	{
		//Keyboard Inputs
		m_previousKeyboardState = m_keyboardState;
		const bool* keyboardState = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardState, keyboardState + m_keyboardState.size(), m_keyboardState.begin());
		
		//Mouse Inputs
		m_previousMousePosition = m_mousePosition;
		m_previousMouseButtonState = m_mouseButtonState;

		uint32_t mouseButtonState = SDL_GetMouseState(&m_mousePosition.x, &m_mousePosition.y);

		m_mouseButtonState[0] = mouseButtonState & SDL_BUTTON_LMASK; // Left mouse button
		m_mouseButtonState[1] = mouseButtonState & SDL_BUTTON_MMASK; // Middle mouse button
		m_mouseButtonState[2] = mouseButtonState & SDL_BUTTON_RMASK; // Right mouse button
	}
}