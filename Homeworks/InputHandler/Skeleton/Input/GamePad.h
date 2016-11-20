#pragma once

//Source = https://lcmccauley.wordpress.com/2014/01/05/gamepad-input-tutorial/

#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <windows.h>
#include <Xinput.h>

namespace InputMapping {

// XInput Button values
static const WORD XINPUT_Buttons[] = {
	XINPUT_GAMEPAD_A,
	XINPUT_GAMEPAD_B,
	XINPUT_GAMEPAD_X,
	XINPUT_GAMEPAD_Y,
	XINPUT_GAMEPAD_DPAD_UP,
	XINPUT_GAMEPAD_DPAD_DOWN,
	XINPUT_GAMEPAD_DPAD_LEFT,
	XINPUT_GAMEPAD_DPAD_RIGHT,
	XINPUT_GAMEPAD_LEFT_SHOULDER,
	XINPUT_GAMEPAD_RIGHT_SHOULDER,
	XINPUT_GAMEPAD_LEFT_THUMB,
	XINPUT_GAMEPAD_RIGHT_THUMB,
	XINPUT_GAMEPAD_START,
	XINPUT_GAMEPAD_BACK
};

// XInput Button IDs
struct XButtonIDs
{
	// Function prototypes
	//---------------------//

	XButtonIDs(); // Default constructor

				  // Member variables
				  //---------------------//

	int A, B, X, Y; // 'Action' buttons

					// Directional Pad (D-Pad)
	int DPad_Up, DPad_Down, DPad_Left, DPad_Right;

	// Shoulder ('Bumper') buttons
	int L_Shoulder, R_Shoulder;

	// Thumbstick buttons
	int L_Thumbstick, R_Thumbstick;

	int Start; // 'START' button
	int Back;  // 'BACK' button
};

class Gamepad
{
	friend class InputHandler;
	friend class GamepadInputHandler;
public:
	// Function prototypes
	//---------------------//

	// Constructors
	Gamepad() = delete;
	Gamepad( Gamepad &) = delete;
	Gamepad( Gamepad &&) = delete;
	Gamepad(int controllerIndex);

	void Update();       // Update gamepad state
	void RefreshState(); // Update button states for next frame

						 // Thumbstick functions

	///TODO Return 0 if in deadzone, easier to handle
	float LeftStick_X();  // Return X axis of left stick
	float LeftStick_Y();  // Return Y axis of left stick
	float RightStick_X(); // Return X axis of right stick
	float RightStick_Y(); // Return Y axis of right stick

	//					  // Trigger functions
	float LeftTrigger();  // Return value of left trigger
	float RightTrigger(); // Return value of right trigger

	//					  // Button functions
	//					  // - 'Pressed' - Return true if pressed, false if not
	//					  // - 'Down'    - Same as 'Pressed', but ONLY on current frame
	bool GetButtonPressed(int );
	bool GetButtonDown(int );

	//// Utility functions
	XINPUT_STATE GetState(); // Return gamepad state
	size_t GetIndex();          // Return gamepad index
	bool Connected();        // Return true if gamepad is connected

	//						 // Vibrate the gamepad (0.0f cancel, 1.0f max speed)
	void Vibrate(float a_fLeftMotor = 0.0f, float a_fRightMotor = 0.0f);

private:
	// - Return true if stick is inside deadzone, false if outside
	bool LStick_InDeadzone();
	bool RStick_InDeadzone();

	// Member variables
	//---------------------//

	XINPUT_STATE m_State; // Current gamepad state
	size_t m_iGamepadIndex;  // Gamepad index (eg. 1,2,3,4)

	static const size_t ButtonCount = 14;    // Total gamepad buttons
	bool bPrev_ButtonStates[ButtonCount]; // Previous frame button states
	bool bButtonStates[ButtonCount];      // Current frame button states

										  
	bool bGamepad_ButtonsReleased[ButtonCount];    //Actual frame button released
	bool bGamepad_ButtonsDown[ButtonCount];    //Actual frame button pressed
};

#endif // GAMEPAD_H

// Externally define the 'XButtonIDs' struct as 'XButtons'
extern XButtonIDs XButtons;

} //NS Input Mapping