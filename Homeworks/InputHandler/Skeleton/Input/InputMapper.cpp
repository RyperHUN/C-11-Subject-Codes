#pragma once

#include "InputMapper.h"
#include "../FileIO.h"
#include <fstream>
#include "InputContext.h"
#include <SDL2/SDL_scancode.h>

namespace InputMapping {

template class InputMapper<RawInputComputer>;
template class InputMapper<RawGamePadInput>;
template class InputMapper<SDL_Scancode>;

template <typename InputType>
InputMapper<InputType>::InputMapper(std::string contextsFile)
{
	unsigned count;
	std::ifstream infile(contextsFile);
	if (!(infile >> count))
		throw std::exception("Failed to read ContextList.txt");
	for (unsigned i = 0; i < count; ++i)
	{
		std::string name = AttemptRead<std::string>(infile);
		std::string file = AttemptRead<std::string>(infile);
		InputContexts[name] = new InputContext<InputType>(file);
	}
}

template <typename InputType>
void InputMapper<InputType>::PressRawButton(InputType button)
{
	Action action;
	State state;
	for (InputContext<InputType>* context : ActiveContexts)
	{
		if (context->MapButtonToAction(button, action))
		{
			CurrentMappedInput.Action.insert(action);
			return;
		}
		if (context->MapButtonToState(button, state))
		{
			CurrentMappedInput.State.insert(state);
			return;
		}
	}
}
template <typename InputType>
void InputMapper<InputType>::ReleaseRawButton(InputType button)
{
	Action action;
	State state;
	for (InputContext<InputType>* context : ActiveContexts)
	{
		if (context->MapButtonToAction(button, action))
		{
			CurrentMappedInput.EatAction(action);
			return;
		}
		if (context->MapButtonToState(button, state))
		{
			CurrentMappedInput.EatState(state);
			return;
		}
	}
}
template <typename InputType>
void InputMapper<InputType>::SetRawAxisValue(InputType axis, double value)
{
	Range range;
	for (InputContext<InputType>* context : ActiveContexts) {
		if (context->MapAxisToRange(axis, range))
			CurrentMappedInput.Ranges[range] = value;
	}
}

//
// Push an active input context onto the stack
//
template <typename InputType>
void InputMapper<InputType>::PushContext(const std::string& name)
{
	std::map<std::string, InputContext<InputType>*>::iterator iter = InputContexts.find(name);
	if (iter == InputContexts.end())
		throw std::exception("Invalid input context pushed");

	ActiveContexts.push_front(iter->second);
}

//
// Pop the current input context off the stack
//
template <typename InputType>
void InputMapper<InputType>::PopContext()
{
	if (ActiveContexts.empty())
		throw std::exception("Cannot pop input context, no contexts active!");

	ActiveContexts.pop_front();
}

} //NS InputMapping