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

	struct StringToAction : public std::map<std::string, Action>
	{
		StringToAction ()
		{
			this->operator[]("Teleport") = Action::Teleport;
		}
		~StringToAction() {}
	};

	struct StringToRange : public std::map<std::string, Range>
	{
		StringToRange ()
		{
			this->operator[]("MoveX") = Range::MoveX;
			this->operator[]("MoveY") = Range::MoveY;
		}
		~StringToRange() {}
	};

	struct StringToState : public std::map<std::string, State>
	{
		StringToState ()
		{
			this->operator[]("Sprint") = State::Sprint;
		}
		~StringToState() {}
	};

	struct ActionToString : public std::map<Action, std::string> 
	{
		ActionToString ()
		{
			this->operator[](Action::Teleport) = "Teleport";
		}
		~ActionToString() {}
	};

	struct RangeToString : public std::map<Range, std::string> 
	{
		RangeToString ()
		{
			this->operator[](Range::MoveX) = "MoveX";
			this->operator[](Range::MoveY) = "MoveY";
		}
		~RangeToString() {}
	};

	struct StateToString : public std::map<State, std::string> 
	{
		StateToString ()
		{
			this->operator[](State::Sprint) = "Sprint";
		}
		~StateToString() {}
	};

}
