#include "GamePad.h"
#include <windows.h>

//#ifdef MSC_VER < 1700
//#pragma comment(lib,"Xinput.lib")
//#else
#pragma comment(lib,"Xinput9_1_0.lib")
//#endif

namespace InputMapping {
// Define the 'XButtonIDs' struct as 'XButtons'
XButtonIDs XButtons;

// 'XButtonIDs' - Default constructor
XButtonIDs::XButtonIDs()
{
	// These values are used to index the XINPUT_Buttons array,
	// accessing the matching XINPUT button value
	A = 0;
	B = 1;
	X = 2;
	Y = 3;

	DPad_Up = 4;
	DPad_Down = 5;
	DPad_Left = 6;
	DPad_Right = 7;

	L_Shoulder = 8;
	R_Shoulder = 9;

	L_Thumbstick = 10;
	R_Thumbstick = 11;

	Start = 12;
	Back = 13;
}

// index 1-4
Gamepad::Gamepad(int controllerIndex)
{
	// in XInput the xbox controller is identified from 0-3
	m_iGamepadIndex = controllerIndex - 1; 

	// Iterate through all gamepad buttons
	for (int i = 0; i < ButtonCount; i++)
	{
		bPrev_ButtonStates[i]       = false;
		bButtonStates[i]            = false;
		bGamepad_ButtonsDown[i]     = false;
		bGamepad_ButtonsReleased[i] = false;
	}
}

// Return gamepad state
XINPUT_STATE Gamepad::GetState()
{
	// Temporary XINPUT_STATE to return
	XINPUT_STATE GamepadState;

	ZeroMemory(&GamepadState, sizeof(XINPUT_STATE));

	// Get the state of the gamepad
	XInputGetState(m_iGamepadIndex, &GamepadState);

	// Return the gamepad state
	return GamepadState;
}

// Return gamepad index
size_t Gamepad::GetIndex()
{
	return m_iGamepadIndex;
}

// Update gamepad state
void Gamepad::Update()
{
	m_State = GetState(); // Obtain current gamepad state
	RefreshState ();
}

void Gamepad::RefreshState()
{
	// Iterate through all gamepad buttons
	for (int i = 0; i < ButtonCount; i++)
	{
		// Set button state for current frame
		bButtonStates[i] = (m_State.Gamepad.wButtons & XINPUT_Buttons[i]) == XINPUT_Buttons[i];

		// Set 'DOWN' state for current frame
		bGamepad_ButtonsDown[i] = !bPrev_ButtonStates[i] && bButtonStates[i];
		bGamepad_ButtonsReleased[i] = bPrev_ButtonStates[i] && !bButtonStates[i];
	}
	memcpy(bPrev_ButtonStates, bButtonStates,
		sizeof(bPrev_ButtonStates));
}

// Return X axis of left stick
float Gamepad::LeftStick_X()
{
	if (!LStick_InDeadzone ()) 
	{
		// Obtain X axis of left stick
		short sX = m_State.Gamepad.sThumbLX;

		// Return axis value, converted to a float
		return (static_cast<float>(sX) / 32768.0f);
	}
	return 0.0f;
}

// Return Y axis of left stick
float Gamepad::LeftStick_Y()
{
	if (!LStick_InDeadzone())
	{
		// Obtain Y axis of left stick
		short sY = m_State.Gamepad.sThumbLY;

		// Return axis value, converted to a float
		return (static_cast<float>(sY) / 32768.0f);
	}
	return 0.0f;
}

// Return X axis of right stick
float Gamepad::RightStick_X()
{
	if (!RStick_InDeadzone())
	{
		// Obtain X axis of right stick
		short sX = m_State.Gamepad.sThumbRX;

		// Return axis value, converted to a float
		return (static_cast<float>(sX) / 32768.0f);
	}
	return 0.0f;
}

// Return Y axis of right stick
float Gamepad::RightStick_Y()
{
	if (!RStick_InDeadzone())
	{
		// Obtain the Y axis of the left stick
		short sY = m_State.Gamepad.sThumbRY;

		// Return axis value, converted to a float
		return (static_cast<float>(sY) / 32768.0f);
	}
	return 0.0f;
}

// Return value of left trigger
float Gamepad::LeftTrigger()
{
	// Obtain value of left trigger
	BYTE Trigger = m_State.Gamepad.bLeftTrigger;

	if (Trigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		return Trigger / 255.0f;

	return 0.0f; // Trigger was not pressed
}

// Return value of right trigger
float Gamepad::RightTrigger()
{
	// Obtain value of right trigger
	BYTE Trigger = m_State.Gamepad.bRightTrigger;

	if (Trigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		return Trigger / 255.0f;

	return 0.0f; // Trigger was not pressed
}

// Return true if button is pressed, false if not
bool Gamepad::GetButtonPressed(int buttonId)
{
	if (m_State.Gamepad.wButtons & XINPUT_Buttons[buttonId])
	{
		return true; // The button is pressed
	}

	return false; // The button is not pressed
}

bool Gamepad::GetButtonDown(int buttonId)
{
	return bGamepad_ButtonsDown[buttonId];
}

// Return true if the gamepad is connected
bool Gamepad::Connected()
{
	// Zero memory
	ZeroMemory(&m_State, sizeof(XINPUT_STATE));

	// Get the state of the gamepad
	DWORD Result = XInputGetState(m_iGamepadIndex, &m_State);

	if (Result == ERROR_SUCCESS)
		return true;  // The gamepad is connected
	else
		return false; // The gamepad is not connected
}

// Vibrate the gamepad (values of 0.0f to 1.0f only)
void Gamepad::Vibrate(float a_fLeftMotor, float a_fRightMotor)
{
	// Vibration state
	XINPUT_VIBRATION VibrationState;

	// Zero memory
	ZeroMemory(&VibrationState, sizeof(XINPUT_VIBRATION));

	// Calculate vibration values
	int iLeftMotor = int(a_fLeftMotor * 65535.0f);
	int iRightMotor = int(a_fRightMotor * 65535.0f);

	// Set vibration values
	VibrationState.wLeftMotorSpeed = iLeftMotor;
	VibrationState.wRightMotorSpeed = iRightMotor;

	// Set the vibration state
	XInputSetState(m_iGamepadIndex, &VibrationState);
}

// Deadzone check for Left Thumbstick
bool Gamepad::LStick_InDeadzone()
{
	// Obtain the X & Y axes of the stick
	short sX = m_State.Gamepad.sThumbLX;
	short sY = m_State.Gamepad.sThumbLY;

	// X axis is outside of deadzone
	if (sX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		sX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;

	// Y axis is outside of deadzone
	if (sY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		sY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;

	// One (or both axes) axis is inside of deadzone
	return true;
}

// Deadzone check for Right Thumbstick
bool Gamepad::RStick_InDeadzone()
{
	// Obtain the X & Y axes of the stick
	short sX = m_State.Gamepad.sThumbRX;
	short sY = m_State.Gamepad.sThumbRY;

	// X axis is outside of deadzone
	if (sX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		sX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		return false;

	// Y axis is outside of deadzone
	if (sY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		sY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		return false;

	// One (or both axes) axis is inside of deadzone
	return true;
}

} // NS InputMapping