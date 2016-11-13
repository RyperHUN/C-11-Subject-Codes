#pragma once


// Dependencies
#include "RawInputConstants.h"
#include "HighLevelInputConstants.h"
#include "../FileIo.h"

#include <map>
#include <set>
#include <stack>
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
			
		}
		//void SetRawButtonState(RawInputButton button, bool pressed, bool previouslypressed);
		//void SetRawAxisValue(RawInputAxis axis, double value);

		// Input dispatching interface
	public:
		//void FireCallbacks() const;

		// Input callback registration interface
	public:
		//void AddCallback(InputCallback callback, int priority);

		// Context management interface
	public:
		void PushContext(const std::wstring& name);
		void PopContext();

		// Internal tracking
	private:
		std::map<std::string, InputContext*> InputContexts;
		std::stack<InputContext*> ActiveContexts;

		std::multimap<int, InputCallback> CallbackTable; //If contexts are same => we can register more callbacks

		MappedInput CurrentMappedInput;
	};
}