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

	struct StringToRawInputComputer : public std::map<std::string, RawInputComputer>
	{
		StringToRawInputComputer ()
		{
			this->operator[]("RAW_INPUT_BUTTON_W") = RawInputComputer::RAW_INPUT_BUTTON_W;
			this->operator[]("RAW_INPUT_BUTTON_A") = RawInputComputer::RAW_INPUT_BUTTON_A;
			this->operator[]("RAW_INPUT_BUTTON_S") = RawInputComputer::RAW_INPUT_BUTTON_S;
			this->operator[]("RAW_INPUT_BUTTON_D") = RawInputComputer::RAW_INPUT_BUTTON_D;
			this->operator[]("RAW_INPUT_BUTTON_K") = RawInputComputer::RAW_INPUT_BUTTON_K;
			this->operator[]("RAW_INPUT_BUTTON_L") = RawInputComputer::RAW_INPUT_BUTTON_L;
			this->operator[]("RAW_INPUT_AXIS_MOUSE_X") = RawInputComputer::RAW_INPUT_AXIS_MOUSE_X;
			this->operator[]("RAW_INPUT_AXIS_MOUSE_Y") = RawInputComputer::RAW_INPUT_AXIS_MOUSE_Y;
		}
		~StringToRawInputComputer() {}
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
			this->operator[]("L_ThumbAxisX") = RawGamePadInput::L_ThumbAxisX;
			this->operator[]("L_ThumbAxisY") = RawGamePadInput::L_ThumbAxisY;
			this->operator[]("R_ThumbAxisX") = RawGamePadInput::R_ThumbAxisX;
			this->operator[]("R_ThumbAxisY") = RawGamePadInput::R_ThumbAxisY;
			this->operator[]("L_TriggerAxis") = RawGamePadInput::L_TriggerAxis;
			this->operator[]("R_TriggerAxis") = RawGamePadInput::R_TriggerAxis;
		}
		~StringToRawGamePadInput() {}
	};

	struct RawInputComputerToString : public std::map<RawInputComputer, std::string> 
	{
		RawInputComputerToString ()
		{
			this->operator[](RawInputComputer::RAW_INPUT_BUTTON_W) = "RAW_INPUT_BUTTON_W";
			this->operator[](RawInputComputer::RAW_INPUT_BUTTON_A) = "RAW_INPUT_BUTTON_A";
			this->operator[](RawInputComputer::RAW_INPUT_BUTTON_S) = "RAW_INPUT_BUTTON_S";
			this->operator[](RawInputComputer::RAW_INPUT_BUTTON_D) = "RAW_INPUT_BUTTON_D";
			this->operator[](RawInputComputer::RAW_INPUT_BUTTON_K) = "RAW_INPUT_BUTTON_K";
			this->operator[](RawInputComputer::RAW_INPUT_BUTTON_L) = "RAW_INPUT_BUTTON_L";
			this->operator[](RawInputComputer::RAW_INPUT_AXIS_MOUSE_X) = "RAW_INPUT_AXIS_MOUSE_X";
			this->operator[](RawInputComputer::RAW_INPUT_AXIS_MOUSE_Y) = "RAW_INPUT_AXIS_MOUSE_Y";
		}
		~RawInputComputerToString() {}
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
			this->operator[](RawGamePadInput::L_ThumbAxisX) = "L_ThumbAxisX";
			this->operator[](RawGamePadInput::L_ThumbAxisY) = "L_ThumbAxisY";
			this->operator[](RawGamePadInput::R_ThumbAxisX) = "R_ThumbAxisX";
			this->operator[](RawGamePadInput::R_ThumbAxisY) = "R_ThumbAxisY";
			this->operator[](RawGamePadInput::L_TriggerAxis) = "L_TriggerAxis";
			this->operator[](RawGamePadInput::R_TriggerAxis) = "R_TriggerAxis";
		}
		~RawGamePadInputToString() {}
	};

}
