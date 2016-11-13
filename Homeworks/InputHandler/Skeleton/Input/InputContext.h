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
			return true;
		}
		bool MapButtonToState(RawInputButton button, State& out) const
		{
			return true;
		}
		bool MapAxisToRange(RawInputAxis axis, Range& out) const
		{
			return false;
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
