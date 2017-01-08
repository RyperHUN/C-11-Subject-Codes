#pragma once
#include <map>

namespace InputMapping
{

	enum RawInputComputer
	{
		RAW_INPUT_BUTTON_W,
		RAW_INPUT_BUTTON_A,
		RAW_INPUT_BUTTON_S,
		RAW_INPUT_BUTTON_D,
		RAW_INPUT_BUTTON_K,
		RAW_INPUT_BUTTON_L,
		RAW_INPUT_AXIS_MOUSE_X,
		RAW_INPUT_AXIS_MOUSE_Y,
	};

	enum RawGamePadInput
	{
		A,
		B,
		X,
		Y,
		DPad_Up,
		DPad_Down,
		DPad_Left,
		DPad_Right,
		L_Shoulder,
		R_Shoulder,
		L_Thumbstick,
		R_Thumbstick,
		Start,
		Back,
		L_ThumbAxisX,
		L_ThumbAxisY,
		R_ThumbAxisX,
		R_ThumbAxisY,
		L_TriggerAxis,
		R_TriggerAxis,
	};

}
