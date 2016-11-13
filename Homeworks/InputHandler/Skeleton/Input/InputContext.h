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

	class InputContext
	{
		friend class InputMappingSerializer;
		// Construction and destruction
	public:
		explicit InputContext(const std::string& contextfilename)
		{
			std::ifstream infile(contextfilename.c_str());

			unsigned rangecount = AttemptRead<unsigned>(infile);
			validRange.resize (rangecount);
			for (unsigned i = 0; i < rangecount; ++i)
			{
				RawInputAxis axis = static_cast<RawInputAxis>(AttemptRead<unsigned>(infile));
				Range range = static_cast<Range>(AttemptRead<unsigned>(infile));
				validRange[axis] = range;
			}

			unsigned statecount = AttemptRead<unsigned>(infile);
			for (unsigned i = 0; i < statecount; ++i)
			{
				RawInputButton button = static_cast<RawInputButton>(AttemptRead<unsigned>(infile));
				State state = static_cast<State>(AttemptRead<unsigned>(infile));
				/*validState.push_back(button) = state;*/
			}

			unsigned actioncount = AttemptRead<unsigned>(infile);
			for (unsigned i = 0; i < actioncount; ++i)
			{
				RawInputButton button = static_cast<RawInputButton>(AttemptRead<unsigned>(infile));
				Action action = static_cast<Action>(AttemptRead<unsigned>(infile));
				//ActionMap[button] = action;
			}

			//Conversions = new RangeConverter(infile);

			unsigned sensitivitycount = AttemptRead<unsigned>(infile);
			for (unsigned i = 0; i < sensitivitycount; ++i)
			{
				Range range = static_cast<Range>(AttemptRead<unsigned>(infile));
				double sensitivity = AttemptRead<double>(infile);
				//SensitivityMap[range] = sensitivity;
			}
		}
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
		std::vector<Action> validAction;
		std::vector<State>  validState;
		std::vector<Range>  validRange;

		std::vector<double> SensitivityMap; //Key is Range
		//RangeConverter* Conversions;
	};

}
