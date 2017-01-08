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
#include "Input/Keyboard.h"
#include <SDL2/SDL_scancode.h>

namespace InputMapping {

static void createGamepadContextFromCode() {
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

static void createKeyboardContextFromCode() {
	ContextCreator<SDL_Keyboard::KeyType>
		("ContextMainKeyboard.txt",
		{ // Ranges
			std::make_pair(SDL_SCANCODE_RIGHT, Range::MoveX),
			std::make_pair(SDL_SCANCODE_UP, Range::MoveY)
		},
		{ // States
			std::make_pair(SDL_SCANCODE_LSHIFT, State::Sprint)
		},
		{ // Actions
			std::make_pair(SDL_SCANCODE_SPACE, Action::Teleport)
		});
}



class KeyboardInputHandler {
	KeyboardInputHandler(KeyboardInputHandler &) = delete;
	KeyboardInputHandler(KeyboardInputHandler &&) = delete;

	KeyboardInputHandler()
	{
		createKeyboardContextFromCode();

		keyboardHandler = InputMapperPtr(new InputMapperType("ContextGamepad.txt"));
		keyboardHandler->PushContext("maincontext");
	}

	void AddCallback(std::function<void(MappedInput&)> callback)
	{
		keyboardHandler->AddCallback(callback, 0);
	}

	void UpdateKeyboard()
	{
		auto const& mapper = keyboardHandler;

		keyboard->Update();

		// The i equals the XButtonIDs, and the Enums values
		for (size_t i = 0; i < keyboard->ButtonCount; i++)
		{
			if (keyboard->bGamepad_ButtonsDown[i])
				mapper->PressRawButton(static_cast<SDL_Keyboard::KeyType> (i));
			if (keyboard->bGamepad_ButtonsReleased[i])
				mapper->ReleaseRawButton(static_cast<SDL_Keyboard::KeyType> (i));
		}
		//Assign axises
		mapper->SetRawAxisValue(SDL_Keyboard::KeyType::SDL_SCANCODE_RIGHT, keyboard->ArrowRight ());
		mapper->SetRawAxisValue(SDL_Keyboard::KeyType::SDL_SCANCODE_UP, keyboard->ArrowUp());

		mapper->FireCallbacks();
		mapper->Clear();
	}
private:
	using InputMapperType = InputMapper<SDL_Keyboard::KeyType>;
	using InputMapperPtr = std::unique_ptr<InputMapperType>;
	InputMapperPtr keyboardHandler;

	using KeyboardPtr = std::unique_ptr<SDL_Keyboard>;
	KeyboardPtr keyboard;
};

class GamepadInputHandler {
public:
	GamepadInputHandler (GamepadInputHandler &)  = delete;
	GamepadInputHandler (GamepadInputHandler &&) = delete;
	GamepadInputHandler () = delete;

	GamepadInputHandler (size_t numberOfControllers )
	{
		createGamepadContextFromCode();
		gamepadHandlers.reserve (numberOfControllers);
		gamepads.reserve (numberOfControllers);
		for (size_t i = 0; i < numberOfControllers; i++)
		{
			//Emplace back == placement new
			gamepadHandlers.push_back (InputMapperPtr(new InputMapperType("ContextGamepad.txt")));
			gamepadHandlers[i]->PushContext ("maincontext");

			gamepads.emplace_back (GamepadPtr (new Gamepad (i + 1)));
		}

		assert (gamepads.size() == gamepadHandlers.size());
	}

	void AddCallback(std::function<void(MappedInput&)> callback, size_t gamepadIndex)
	{
		assert (gamepadIndex < gamepadHandlers.size ());

		gamepadHandlers [gamepadIndex]->AddCallback (callback, 0);
	}
	void AddCallbackAll(std::function<void(MappedInput&)> callback)
	{
		for (InputMapperPtr& inputMapper : gamepadHandlers) 
		{
			inputMapper->AddCallback (callback, 0);
		}
	}
	void UpdateGamepads ()
	{
		assert (gamepads.size () == gamepadHandlers.size ());

		for (size_t i = 0; i < gamepads.size (); i++)
		{
			auto const& gamepad = gamepads[i];
			auto const& mapper  = gamepadHandlers[i];
			
			///TODO Better not conected gamepad handler
			if (gamepad->Connected()) {
				gamepad->Update();

				// The i equals the XButtonIDs, and the Enums values
				for (size_t i = 0; i < gamepad->ButtonCount; i++)
				{
					if (gamepad->bGamepad_ButtonsDown[i])
						mapper->PressRawButton(static_cast<RawGamePadInput> (i));
					if (gamepad->bGamepad_ButtonsReleased[i])
						mapper->ReleaseRawButton(static_cast<RawGamePadInput> (i));
				}
				//Assign axises
				mapper->SetRawAxisValue(InputMapping::RawGamePadInput::L_ThumbAxisX, gamepad->LeftStick_X());
				mapper->SetRawAxisValue(InputMapping::RawGamePadInput::L_ThumbAxisY, gamepad->LeftStick_Y());
				mapper->SetRawAxisValue(InputMapping::RawGamePadInput::R_ThumbAxisX, gamepad->RightStick_Y());
				mapper->SetRawAxisValue(InputMapping::RawGamePadInput::R_ThumbAxisY, gamepad->RightStick_Y());
				mapper->SetRawAxisValue(InputMapping::RawGamePadInput::R_TriggerAxis, gamepad->RightTrigger());
				mapper->SetRawAxisValue(InputMapping::RawGamePadInput::L_TriggerAxis, gamepad->LeftTrigger());

				mapper->FireCallbacks();
				mapper->Clear();
			}
		}
	}
private:
	using InputMapperType = InputMapper<RawGamePadInput>;
	using InputMapperPtr  = std::unique_ptr<InputMapperType>;
	std::vector<InputMapperPtr> gamepadHandlers;

	using GamepadPtr = std::unique_ptr<Gamepad>;
	std::vector<GamepadPtr> gamepads;
};



} // NS InputMapper


