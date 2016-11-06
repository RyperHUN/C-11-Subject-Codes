#pragma once
#include <map>

namespace InputMapping
{

	enum RawInpuButton
	{
		RAW_INPUT_BUTTON_W,
		RAW_INPUT_BUTTON_A,
		RAW_INPUT_BUTTON_S,
		RAW_INPUT_BUTTON_D,
	};

	enum RawInputAxis
	{
		RAW_INPUT_AXIS_MOUSE_X,
		RAW_INPUT_AXIS_MOUSE_Y,
	};

	struct StringToRawInpuButton : public std::map<std::string, RawInpuButton>
	{
		StringToRawInpuButton ()
		{
			this->operator[]("RAW_INPUT_BUTTON_W") = RawInpuButton::RAW_INPUT_BUTTON_W;
			this->operator[]("RAW_INPUT_BUTTON_A") = RawInpuButton::RAW_INPUT_BUTTON_A;
			this->operator[]("RAW_INPUT_BUTTON_S") = RawInpuButton::RAW_INPUT_BUTTON_S;
			this->operator[]("RAW_INPUT_BUTTON_D") = RawInpuButton::RAW_INPUT_BUTTON_D;
		}
		~StringToRawInpuButton() {}
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

}
