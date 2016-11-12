#pragma once


// Dependencies
#include "RawInputConstants.h"
#include "HighLevelInputConstants.h"
//#include "RangeConverter.h"
#include <map>


namespace InputMapping
{

	class InputContext
	{
		friend class InputMappingSerializer;
		// Construction and destruction
	public:
		explicit InputContext(const std::wstring& contextfilename);
		//~InputContext();

		// Mapping interface
	public:
		//bool MapButtonToAction(RawInputButton button, Action& out) const;
		//bool MapButtonToState(RawInputButton button, State& out) const;
		//bool MapAxisToRange(RawInputAxis axis, Range& out) const;

		//double GetSensitivity(Range range) const;

		//const RangeConverter& GetConversions() const
		//{
		//	return *Conversions;
		//}

		// Internal tracking
	private:
		std::map<RawInputButton, Actions> ActionMap;
		std::map<RawInputButton, States> StateMap;
		std::map<RawInputAxis, Axises> RangeMap;

		std::map<Axises, double> SensitivityMap;
		//RangeConverter* Conversions;
	};

}
