#pragma once

#include <vector>
#include <memory>
#include <cassert>
#include <iostream>

#include "Input/GamePad.h"
#include "Input/HighLevelInputConstants.h"
#include "Input/RawInputConstants.h"
#include "Input/InputMapper.h"
#include "Input/InputContext.h"

namespace InputMapping {

	class Keyboard; ///TODO

class InputHandler
{
public:
	InputHandler () 
	{
		keyboardHandlers.push_back (new InputMapper<RawInputComputer> ("KeyboardContexts.txt"));

		gamepadHandlers.push_back(new InputMapper<RawGamePadInput>("KeyboardContexts.txt"));
	}
	void handleGamepad (Gamepad& gamepad)
	{
		assert (gamepad.GetIndex () < gamepadHandlers.size ());

		auto mapper = gamepadHandlers[gamepad.GetIndex ()];

		///TODO Assign pushed and relased buttons
		mapper->SetRawAxisValue (InputMapping::RawGamePadInput::L_ThumbAxisX, gamepad.LeftStick_X ());

		mapper->AddCallback ([](MappedInput &) { std::cout << "FIRE - "; } , 0);
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


