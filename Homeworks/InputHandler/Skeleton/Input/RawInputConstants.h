#pragma once
#include <map>

namespace InputMapping
{

	enum RawInputButton
	{
		RAW_INPUT_BUTTON_W,
		RAW_INPUT_BUTTON_A,
		RAW_INPUT_BUTTON_S,
		RAW_INPUT_BUTTON_D,
		RAW_INPUT_BUTTON_K,
		RAW_INPUT_BUTTON_L,
	};

	enum RawInputAxis
	{
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
	};

	struct StringToRawInputButton : public std::map<std::string, RawInputButton>
	{
		StringToRawInputButton ()
		{
			this->operator[]("RAW_INPUT_BUTTON_W") = RawInputButton::RAW_INPUT_BUTTON_W;
			this->operator[]("RAW_INPUT_BUTTON_A") = RawInputButton::RAW_INPUT_BUTTON_A;
			this->operator[]("RAW_INPUT_BUTTON_S") = RawInputButton::RAW_INPUT_BUTTON_S;
			this->operator[]("RAW_INPUT_BUTTON_D") = RawInputButton::RAW_INPUT_BUTTON_D;
			this->operator[]("RAW_INPUT_BUTTON_K") = RawInputButton::RAW_INPUT_BUTTON_K;
			this->operator[]("RAW_INPUT_BUTTON_L") = RawInputButton::RAW_INPUT_BUTTON_L;
		}
		~StringToRawInputButton() {}
	};

	struct StringToRawInputAxis : public std::map<std::string, RawInputAxis>
	{
		StringToRawInputAxis ()
		{
			this->operator[]("RAW_INPUT_AXIS_MOUSE_X") = RawInputAxis::RAW_INPUT_AXIS_MOUSE_X;
			this->operator[]("RAW_INPUT_AXIS_MOUSE_Y") = RawInputAxis::RAW_INPUT_AXIS_MOUSE_Y;
		}
		~StringToRawInputAxis() {}
	};

	struct StringToRawGamePadInput : public std::map<std::string, RawGamePadInput>
	{
		StringToRawGamePadInput ()
		{
			this->operator[]("A") = RawGamePadInput::A;
			this->operator[]("B") = RawGamePadInput::B;
			this->operator[]("X") = RawGamePadInput::X;
			this->operator[]("Y") = RawGamePadInput::Y;
			this->operator[]("DPad_Up") = RawGamePadInput::DPad_Up;
			this->operator[]("DPad_Down") = RawGamePadInput::DPad_Down;
			this->operator[]("DPad_Left") = RawGamePadInput::DPad_Left;
			this->operator[]("DPad_Right") = RawGamePadInput::DPad_Right;
			this->operator[]("L_Shoulder") = RawGamePadInput::L_Shoulder;
			this->operator[]("R_Shoulder") = RawGamePadInput::R_Shoulder;
			this->operator[]("L_Thumbstick") = RawGamePadInput::L_Thumbstick;
			this->operator[]("R_Thumbstick") = RawGamePadInput::R_Thumbstick;
			this->operator[]("Start") = RawGamePadInput::Start;
			this->operator[]("Back") = RawGamePadInput::Back;
		}
		~StringToRawGamePadInput() {}
	};

	struct RawInputButtonToString : public std::map<RawInputButton, std::string> 
	{
		RawInputButtonToString ()
		{
			this->operator[](RawInputButton::RAW_INPUT_BUTTON_W) = "RAW_INPUT_BUTTON_W";
			this->operator[](RawInputButton::RAW_INPUT_BUTTON_A) = "RAW_INPUT_BUTTON_A";
			this->operator[](RawInputButton::RAW_INPUT_BUTTON_S) = "RAW_INPUT_BUTTON_S";
			this->operator[](RawInputButton::RAW_INPUT_BUTTON_D) = "RAW_INPUT_BUTTON_D";
			this->operator[](RawInputButton::RAW_INPUT_BUTTON_K) = "RAW_INPUT_BUTTON_K";
			this->operator[](RawInputButton::RAW_INPUT_BUTTON_L) = "RAW_INPUT_BUTTON_L";
		}
		~RawInputButtonToString() {}
	};

	struct RawInputAxisToString : public std::map<RawInputAxis, std::string> 
	{
		RawInputAxisToString ()
		{
			this->operator[](RawInputAxis::RAW_INPUT_AXIS_MOUSE_X) = "RAW_INPUT_AXIS_MOUSE_X";
			this->operator[](RawInputAxis::RAW_INPUT_AXIS_MOUSE_Y) = "RAW_INPUT_AXIS_MOUSE_Y";
		}
		~RawInputAxisToString() {}
	};

	struct RawGamePadInputToString : public std::map<RawGamePadInput, std::string> 
	{
		RawGamePadInputToString ()
		{
			this->operator[](RawGamePadInput::A) = "A";
			this->operator[](RawGamePadInput::B) = "B";
			this->operator[](RawGamePadInput::X) = "X";
			this->operator[](RawGamePadInput::Y) = "Y";
			this->operator[](RawGamePadInput::DPad_Up) = "DPad_Up";
			this->operator[](RawGamePadInput::DPad_Down) = "DPad_Down";
			this->operator[](RawGamePadInput::DPad_Left) = "DPad_Left";
			this->operator[](RawGamePadInput::DPad_Right) = "DPad_Right";
			this->operator[](RawGamePadInput::L_Shoulder) = "L_Shoulder";
			this->operator[](RawGamePadInput::R_Shoulder) = "R_Shoulder";
			this->operator[](RawGamePadInput::L_Thumbstick) = "L_Thumbstick";
			this->operator[](RawGamePadInput::R_Thumbstick) = "R_Thumbstick";
			this->operator[](RawGamePadInput::Start) = "Start";
			this->operator[](RawGamePadInput::Back) = "Back";
		}
		~RawGamePadInputToString() {}
	};

}
