#pragma once

#include "InputMapper.h"
#include "../FileIO.h"
#include <fstream>
#include "InputContext.h"

namespace InputMapping {

InputMapper::InputMapper(std::string contextsFile)
{
	unsigned count;
	std::ifstream infile(contextsFile);
	if (!(infile >> count))
		throw std::exception("Failed to read ContextList.txt");
	for (unsigned i = 0; i < count; ++i)
	{
		std::string name = AttemptRead<std::string>(infile);
		std::string file = AttemptRead<std::string>(infile);
		InputContexts[name] = new InputContext(file);
	}
}

void InputMapper::PressRawButton(RawInputButton button)
{
	Action action;
	State state;
	for (InputContext* context : ActiveContexts)
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

void InputMapper::ReleaseRawButton(RawInputButton button)
{
	Action action;
	State state;
	for (InputContext* context : ActiveContexts)
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

void InputMapper::SetRawAxisValue(RawInputAxis axis, double value)
{
	Range range;
	for (InputContext* context : ActiveContexts) {
		if (context->MapAxisToRange(axis, range))
			CurrentMappedInput.Ranges[range] = value;
	}
}

//
// Push an active input context onto the stack
//
void InputMapper::PushContext(const std::string& name)
{
	std::map<std::string, InputContext*>::iterator iter = InputContexts.find(name);
	if (iter == InputContexts.end())
		throw std::exception("Invalid input context pushed");

	ActiveContexts.push_front(iter->second);
}

//
// Pop the current input context off the stack
//
void InputMapper::PopContext()
{
	if (ActiveContexts.empty())
		throw std::exception("Cannot pop input context, no contexts active!");

	ActiveContexts.pop_front();
}

} //NS InputMapping