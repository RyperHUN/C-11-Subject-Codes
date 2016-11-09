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
	};

	enum RawInputAxis
	{
		RAW_INPUT_AXIS_MOUSE_X,
		RAW_INPUT_AXIS_MOUSE_Y,
	};

	struct StringToRawInputButton : public std::map<std::string, RawInputButton>
	{
		StringToRawInputButton ()
		{
			this->operator[]("RAW_INPUT_BUTTON_W") = RawInputButton::RAW_INPUT_BUTTON_W;
			this->operator[]("RAW_INPUT_BUTTON_A") = RawInputButton::RAW_INPUT_BUTTON_A;
			this->operator[]("RAW_INPUT_BUTTON_S") = RawInputButton::RAW_INPUT_BUTTON_S;
			this->operator[]("RAW_INPUT_BUTTON_D") = RawInputButton::RAW_INPUT_BUTTON_D;
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

}
