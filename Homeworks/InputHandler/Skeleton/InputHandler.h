#pragma once

#include <vector>
#include <memory>
#include <Xinput.h>

#include "../XBOXControllerInputTest/GamePad.h"

class Actor
{
};

class Command 
{
public:
	Command () = delete;
	Command (Actor * actor) : actor(actor) {}
	virtual void execute () = 0;
	virtual ~Command () {}
protected:
	Actor * actor; // TODO Maybe get on execute
};

namespace Commands {
	class NullCommand : public Command 
	{
	public:
		using Command::Command;
		void execute () override 
		{
			return;
		}
	};
} // NS Commands

class CommandChooser {
public:

};

enum RawInputButton
{
	RAW_INPUT_BUTTON_W,
	RAW_INPUT_BUTTON_A,
	RAW_INPUT_BUTTON_S,
	RAW_INPUT_BUTTON_D,
};

class InputHandler
{
public:
	InputHandler (Actor * actor) 
	{
		std::unique_ptr<Command>* buttons[] =  {&buttonA, &buttonW, &buttonS, &buttonD, &buttonShift};
		for (auto button : buttons)
			*button = std::unique_ptr<Command>(new Commands::NullCommand (actor));
	}
	void handlePress (RawInputButton button)
	{
		switch (button)
		{
			case RAW_INPUT_BUTTON_W:
				break;
			case RAW_INPUT_BUTTON_A:
				break;
			case RAW_INPUT_BUTTON_S:
				break;
			case RAW_INPUT_BUTTON_D:
				break;
			default:
				break;
		}
	}
	void handleRelase (RawInputButton button)
	{
		switch (button)
		{
			case RAW_INPUT_BUTTON_W:
				break;
			case RAW_INPUT_BUTTON_A:
				break;
			case RAW_INPUT_BUTTON_S:
				break;
			case RAW_INPUT_BUTTON_D:
				break;
			default:
				break;
		}
	}
private:
	std::unique_ptr<Command> buttonA;
	std::unique_ptr<Command> buttonW;
	std::unique_ptr<Command> buttonS;
	std::unique_ptr<Command> buttonD;
	std::unique_ptr<Command> buttonShift; ///TODO Solve
};


