#pragma once
#include <map>

namespace InputMapping
{

	enum Actions
	{
		Teleport,
	};

	enum Axises
	{
		MoveX,
		MoveY,
	};

	enum States
	{
		Sprint,
	};

	struct StringToActions : public std::map<std::string, Actions>
	{
		StringToActions ()
		{
			this->operator[]("Teleport") = Actions::Teleport;
		}
		~StringToActions() {}
	};

	struct StringToAxises : public std::map<std::string, Axises>
	{
		StringToAxises ()
		{
			this->operator[]("MoveX") = Axises::MoveX;
			this->operator[]("MoveY") = Axises::MoveY;
		}
		~StringToAxises() {}
	};

	struct StringToStates : public std::map<std::string, States>
	{
		StringToStates ()
		{
			this->operator[]("Sprint") = States::Sprint;
		}
		~StringToStates() {}
	};

	struct ActionsToString : public std::map<Actions, std::string> 
	{
		ActionsToString ()
		{
			this->operator[](Actions::Teleport) = "Teleport";
		}
		~ActionsToString() {}
	};

	struct AxisesToString : public std::map<Axises, std::string> 
	{
		AxisesToString ()
		{
			this->operator[](Axises::MoveX) = "MoveX";
			this->operator[](Axises::MoveY) = "MoveY";
		}
		~AxisesToString() {}
	};

	struct StatesToString : public std::map<States, std::string> 
	{
		StatesToString ()
		{
			this->operator[](States::Sprint) = "Sprint";
		}
		~StatesToString() {}
	};

}
