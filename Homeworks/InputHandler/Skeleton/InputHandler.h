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
		{ // States
			std::make_pair(RawGamePadInput::R_Shoulder, State::Sprint)
		},
		{ // Actions
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
		gamepadHandlers[0]->PushContext ("maincontext");
	}
	void handleGamepad (Gamepad& gamepad)
	{
		assert (gamepad.GetIndex () < gamepadHandlers.size ());

		///TODO Only if gamepad connected
		if (gamepad.Connected ())
		{
			auto mapper = gamepadHandlers[gamepad.GetIndex ()];
			gamepad.Update (); // if not called ButtonDown and Relase will not work
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
	}
	void handleKeyboard (Keyboard& keyboard)
	{

	}
	void AddCallback (std::function<void(MappedInput&)> callback)
	{
		auto mapper = *gamepadHandlers.begin ();
		mapper->AddCallback (callback, 0);
	}
private:
	std::vector<InputMapper<RawGamePadInput>*> gamepadHandlers;
	std::vector<InputMapper<RawInputComputer>*> keyboardHandlers;
};

class GamepadInputHandler {
public:
	GamepadInputHandler (size_t numberOfControllers )
	{
		createContextFromCode();
		gamepadHandlers.reserve (numberOfControllers);
		gamepads.reserve (numberOfControllers);
		for (size_t i = 0; i < numberOfControllers; i++)
		{
			//Emplace back == placement new
			gamepadHandlers.emplace_back (new InputMapperPtr(new InputMapperType("ContextGamepad.txt")));
			gamepadHandlers[i]->PushContext ("maincontext");

			gamepads.emplace_back (new std::unique_ptr<Gamepad>)
		}
	}

	void AddCallback(std::function<void(MappedInput&)> callback, size_t gamepad)
	{
		for (auto& inputMapper : gamepadHandlers)
		mapper->AddCallback(callback, 0);
	}
private:
	using InputMapperType = InputMapper<RawGamePadInput>;
	using InputMapperPtr  = std::unique_ptr<InputMapperType>;
	std::vector<InputMapperPtr> gamepadHandlers;

	using GamepadPtr = std::unique_ptr<Gamepad>;
	std::vector<GamepadPtr> gamepads;
};



} // NS InputMapper


