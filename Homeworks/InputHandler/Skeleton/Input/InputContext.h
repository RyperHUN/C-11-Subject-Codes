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
		bool MapButtonToAction(RawInputButton button, Action& out) const
		{
			std::map<RawInputButton, Action>::const_iterator iter = ActionMap.find(button);
			if (iter == ActionMap.end())
				return false;

			out = iter->second;
			return true;
		}
		bool MapButtonToState(RawInputButton button, State& out) const
		{
			std::map<RawInputButton, State>::const_iterator iter = StateMap.find(button);
			if (iter == StateMap.end())
				return false;

			out = iter->second;
			return true;
		}
		bool MapAxisToRange(RawInputAxis axis, Range& out) const
		{
			std::map<RawInputAxis, Range>::const_iterator iter = RangeMap.find(axis);
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
		std::map<RawInputButton, Action> ActionMap;
		std::map<RawInputButton, State> StateMap;
		std::map<RawInputAxis, Range> RangeMap;

		std::map<Range, double> SensitivityMap; //Key is Range
		//RangeConverter* Conversions;
	};

}
