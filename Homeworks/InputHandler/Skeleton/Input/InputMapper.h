#pragma once


// Dependencies
#include "Input/RawInputConstants.h"
#include "Input/HighLevelInputConstants.h"

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
		std::set<Actions> Actions;
		std::set<States> States;
		std::map<Axises, double> Ranges;

		// Consumption helpers
		void EatAction(InputMapping::Actions action) { Actions.erase(action); }
		void EatState(InputMapping::States state) { States.erase(state); }
		void EatRange(Axises /*range*/) {;}
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
		InputMapper();
		~InputMapper();

		// Raw input interface
	public:
		void Clear();
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
		std::map<std::wstring, InputContext*> InputContexts;
		std::stack<InputContext*> ActiveContexts;

		std::multimap<int, InputCallback> CallbackTable;

		MappedInput CurrentMappedInput;
	};
}