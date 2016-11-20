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
	template <typename InputType>
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
		bool MapButtonToAction(InputType button, Action& out) const
		{
			std::map<InputType, Action>::const_iterator iter = ActionMap.find(button);
			if (iter == ActionMap.end())
				return false;

			out = iter->second;
			return true;
		}
		bool MapButtonToState(InputType button, State& out) const
		{
			std::map<InputType, State>::const_iterator iter = StateMap.find(button);
			if (iter == StateMap.end())
				return false;

			out = iter->second;
			return true;
		}
		bool MapAxisToRange(InputType axis, Range& out) const
		{
			std::map<InputType, Range>::const_iterator iter = RangeMap.find(axis);
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
		std::map<InputType, Action> ActionMap;
		std::map<InputType, State> StateMap;
		std::map<InputType, Range> RangeMap;

		std::map<Range, double> SensitivityMap; //Key is Range
		//RangeConverter* Conversions;
	};

}
