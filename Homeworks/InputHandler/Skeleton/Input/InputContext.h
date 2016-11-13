#pragma once


// Dependencies
#include "RawInputConstants.h"
#include "HighLevelInputConstants.h"
//#include "RangeConverter.h"
#include <map>
#include <vector>
#include <fstream>
#include "../fileio.h"

#pragma once

namespace InputMapping
{
	///TODO Maybe template
	class InputContext
	{
		friend class InputMappingSerializer;
		// Construction and destruction
	public:
		explicit InputContext(const std::string& contextfilename);
		~InputContext()
		{
		}

		// Mapping interface
	public:
		bool MapButtonToAction(RawInputComputer button, Action& out) const
		{
			std::map<RawInputComputer, Action>::const_iterator iter = ActionMap.find(button);
			if (iter == ActionMap.end())
				return false;

			out = iter->second;
			return true;
		}
		bool MapButtonToState(RawInputComputer button, State& out) const
		{
			std::map<RawInputComputer, State>::const_iterator iter = StateMap.find(button);
			if (iter == StateMap.end())
				return false;

			out = iter->second;
			return true;
		}
		bool MapAxisToRange(RawInputComputer axis, Range& out) const
		{
			std::map<RawInputComputer, Range>::const_iterator iter = RangeMap.find(axis);
			if (iter == RangeMap.end())
				return false;

			out = iter->second;
			return true;
		}

		//double GetSensitivity(Range range) const;

		//const RangeConverter& GetConversions() const
		//{
		//	return *Conversions;
		//}

		// Internal tracking
	private:
		std::map<RawInputComputer, Action> ActionMap;
		std::map<RawInputComputer, State> StateMap;
		std::map<RawInputComputer, Range> RangeMap;

		std::map<Range, double> SensitivityMap; //Key is Range
		//RangeConverter* Conversions;
	};

}
