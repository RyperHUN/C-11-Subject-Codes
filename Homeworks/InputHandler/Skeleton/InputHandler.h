#pragma once

#include <vector>
#include <memory>
#include <cassert>
#include <iostream>
#include <map>

#include "Input/GamePad.h"
#include "Input/HighLevelInputConstants.h"
#include "Input/RawInputConstants.h"
#include "Input/InputMapper.h"
#include "Input/InputContext.h"
#include "Input/Serializers.h"

namespace InputMapping {

static void createContextFromCode() {
	ContextCreator<RawGamePadInput>
		("ContextMainGamepad.txt",
		{ // Ranges
			std::make_pair(RawGamePadInput::L_ThumbAxisX, Range::MoveX),
			std::make_pair(RawGamePadInput::L_ThumbAxisY, Range::MoveY)
		},
		{ // Ranges
			std::make_pair(RawGamePadInput::R_Shoulder, State::Sprint)
		},
		{ // Ranges
			std::make_pair(RawGamePadInput::X, Action::Teleport)
		});
}

	class Keyboard; ///TODO

class InputHandler
{
public:
	InputHandler () 
	{
		keyboardHandlers.push_back (new InputMapper<RawInputComputer> ("KeyboardContexts.txt"));
		createContextFromCode ();
		gamepadHandlers.push_back(new InputMapper<RawGamePadInput>("ContextGamepad.txt"));
	}
	void handleGamepad (Gamepad& gamepad)
	{
		assert (gamepad.GetIndex () < gamepadHandlers.size ());

		///TODO Only if gamepad connected
		//if (gamepad.Connected ())
		
		auto mapper = gamepadHandlers[gamepad.GetIndex ()];

		for (size_t i = 0; i < gamepad.ButtonCount; i++ )
		{
			if (gamepad.bGamepad_ButtonsDown[i] )
				mapper->PressRawButton (static_cast<RawGamePadInput> (i) );
			if (gamepad.bGamepad_ButtonsReleased[i] )
				mapper->ReleaseRawButton (static_cast<RawGamePadInput> (i));
		}
		//Assign axises
		mapper->SetRawAxisValue(InputMapping::RawGamePadInput::L_ThumbAxisX, gamepad.LeftStick_X ());
		mapper->SetRawAxisValue(InputMapping::RawGamePadInput::L_ThumbAxisY, gamepad.LeftStick_Y ());
		mapper->SetRawAxisValue(InputMapping::RawGamePadInput::R_ThumbAxisX, gamepad.RightStick_Y ());
		mapper->SetRawAxisValue(InputMapping::RawGamePadInput::R_ThumbAxisY, gamepad.RightStick_Y ());
		mapper->SetRawAxisValue(InputMapping::RawGamePadInput::R_TriggerAxis, gamepad.RightTrigger ());
		mapper->SetRawAxisValue(InputMapping::RawGamePadInput::L_TriggerAxis, gamepad.LeftTrigger ());
		
		mapper->FireCallbacks ();
		mapper->Clear ();
	}
	void handleKeyboard (Keyboard& keyboard)
	{

	}
private:
	std::vector<InputMapper<RawGamePadInput>*> gamepadHandlers;
	std::vector<InputMapper<RawInputComputer>*> keyboardHandlers;
};



} // NS InputMapper


