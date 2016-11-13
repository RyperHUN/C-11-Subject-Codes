#pragma once
#include <map>

namespace InputMapping
{

	enum Action
	{
		Teleport,
	};

	enum Range
	{
		MoveX,
		MoveY,
	};

	enum State
	{
		Sprint,
	};

	struct StringToActions : public std::map<std::string, Action>
	{
		StringToActions ()
		{
			this->operator[]("Teleport") = Action::Teleport;
		}
		~StringToActions() {}
	};

	struct StringToAxises : public std::map<std::string, Range>
	{
		StringToAxises ()
		{
			this->operator[]("MoveX") = Range::MoveX;
			this->operator[]("MoveY") = Range::MoveY;
		}
		~StringToAxises() {}
	};

	struct StringToStates : public std::map<std::string, State>
	{
		StringToStates ()
		{
			this->operator[]("Sprint") = State::Sprint;
		}
		~StringToStates() {}
	};

	struct ActionsToString : public std::map<Action, std::string> 
	{
		ActionsToString ()
		{
			this->operator[](Action::Teleport) = "Teleport";
		}
		~ActionsToString() {}
	};

	struct AxisesToString : public std::map<Range, std::string> 
	{
		AxisesToString ()
		{
			this->operator[](Range::MoveX) = "MoveX";
			this->operator[](Range::MoveY) = "MoveY";
		}
		~AxisesToString() {}
	};

	struct StatesToString : public std::map<State, std::string> 
	{
		StatesToString ()
		{
			this->operator[](State::Sprint) = "Sprint";
		}
		~StatesToString() {}
	};

}
