#pragma once


// Dependencies
#include "RawInputConstants.h"
#include "HighLevelInputConstants.h"
#include "../FileIo.h"

#include <map>
#include <set>
#include <vector>
#include <list>
#include <string>


namespace InputMapping
{

	// Forward declarations
	class InputContext;

	class InputMapperSerializer;

	// Helper structure
	struct MappedInput
	{
		std::set<Action> Action;
		std::set<State> State;
		std::map<Range, double> Ranges;

		// Consumption helpers
		void EatAction(InputMapping::Action action) { Action.erase(action); }
		void EatState(InputMapping::State state) { State.erase(state); }
		void EatRange(Range /*range*/) {;}
		//{
		//	std::map<Range, double>::iterator iter = Ranges.find(range);
		//	if (iter != Ranges.end())
		//		Ranges.erase(iter);
		//}
	};


	// Handy type shortcuts
	using InputCallback = void(*)(MappedInput& inputs);

	class InputMapper
	{
		friend class InputMapperSerializer;
		// Construction and destruction
	public:
		InputMapper(std::string contextsFile);
		~InputMapper() {}

		// Raw input interface
	public:
		void Clear() 
		{
			CurrentMappedInput.Action.clear ();
			CurrentMappedInput.Ranges.clear ();
		}
		void PressRawButton (RawInputComputer button);
		void ReleaseRawButton (RawInputComputer button);
		void SetRawAxisValue (RawInputComputer axis, double value);

		// Input dispatching interface
	public:
		void FireCallbacks() const
		{
			MappedInput input = CurrentMappedInput;
			for (std::multimap<int, InputCallback>::const_iterator iter = CallbackTable.begin(); iter != CallbackTable.end(); ++iter)
				iter->second(input);
		}

		// Input callback registration interface
	public:
		void AddCallback(InputCallback callback, int priority)
		{
			CallbackTable.insert(std::make_pair(priority, callback));
		}

		// Context management interface
	public:
		void PushContext(const std::string& name);
		void PopContext();

		// Internal tracking
	private:
		std::map<std::string, InputContext*> InputContexts;
		std::list<InputContext*> ActiveContexts;
		//std::vector<InputContext*> ActiveContexts; ///TODO REVERSE ITERATOR VECTOR, and then we don't need to insert do push_front

		std::multimap<int, InputCallback> CallbackTable; //If contexts are same => we can register more callbacks

		MappedInput CurrentMappedInput;
	};
}