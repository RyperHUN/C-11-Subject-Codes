#include "InputContext.h"

namespace InputMapping {

InputContext::InputContext(const std::string& contextfilename)
{
	std::ifstream infile(contextfilename.c_str());

	unsigned rangecount = AttemptRead<unsigned>(infile);
	for (unsigned i = 0; i < rangecount; ++i)
	{
		RawInputAxis axis = static_cast<RawInputAxis>(AttemptRead<unsigned>(infile));
		Range range = static_cast<Range>(AttemptRead<unsigned>(infile));
		RangeMap[axis] = range;
	}

	unsigned statecount = AttemptRead<unsigned>(infile);
	for (unsigned i = 0; i < statecount; ++i)
	{
		RawInputButton button = static_cast<RawInputButton>(AttemptRead<unsigned>(infile));
		State state = static_cast<State>(AttemptRead<unsigned>(infile));
		StateMap[button] = state;
	}

	unsigned actioncount = AttemptRead<unsigned>(infile);
	for (unsigned i = 0; i < actioncount; ++i)
	{
		RawInputButton button = static_cast<RawInputButton>(AttemptRead<unsigned>(infile));
		Action action = static_cast<Action>(AttemptRead<unsigned>(infile));
		ActionMap[button] = action;
	}

	//Conversions = new RangeConverter(infile);

	unsigned sensitivitycount = AttemptRead<unsigned>(infile);
	for (unsigned i = 0; i < sensitivitycount; ++i)
	{
		Range range = static_cast<Range>(AttemptRead<unsigned>(infile));
		double sensitivity = AttemptRead<double>(infile);
		SensitivityMap[range] = sensitivity;
	}
}

} //NS InputMapping