#pragma once

#include <SDL2/SDL.h>
#include <memory>

namespace InputMapping {

class SDL_Keyboard {
	friend class KeyboardInputHandler;
public:
	using KeyType = SDL_Scancode;

	const Uint8 * GetState()
	{
		return SDL_GetKeyboardState(NULL);
	}

	void Update()
	{
		m_State = GetState(); // Obtain current gamepad state
		RefreshState();
	}

	void RefreshState()
	{
		for (size_t i = 0; i < ButtonCount; i++)
		{
			// Set button state for current frame
			bButtonStates[i] = m_State[i] != 0;

			// Set 'DOWN' state for current frame
			bGamepad_ButtonsDown[i] = !bPrev_ButtonStates[i] && bButtonStates[i];
			bGamepad_ButtonsReleased[i] = bPrev_ButtonStates[i] && !bButtonStates[i];
		}
		memcpy(bPrev_ButtonStates, bButtonStates,
			sizeof(bPrev_ButtonStates));
	}

	int ArrowRight()
	{
		return m_State[SDL_SCANCODE_RIGHT] - m_State[SDL_SCANCODE_LEFT];
	}

	int ArrowUp()
	{
		return m_State[SDL_SCANCODE_UP] - m_State[SDL_SCANCODE_DOWN];
	}
private:
	const Uint8 *m_State = SDL_GetKeyboardState(NULL);
	static const size_t ButtonCount = SDL_SCANCODE_APP2;    // Total gamepad buttons
	bool bPrev_ButtonStates[ButtonCount]; // Previous frame button states
	bool bButtonStates[ButtonCount];      // Current frame button states


	bool bGamepad_ButtonsReleased[ButtonCount];    //Actual frame button released
	bool bGamepad_ButtonsDown[ButtonCount];    //Actual frame button pressed
};

} //NS InputMapping