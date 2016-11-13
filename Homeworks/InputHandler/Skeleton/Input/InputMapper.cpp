#pragma once

#include "InputMapper.h"
#include "../FileIO.h"
#include <fstream>
#include "InputContext.h"

namespace InputMapping {

InputMapper::InputMapper(std::string contextsFile)
{
	unsigned count;
	std::ifstream infile(contextsFile);
	if (!(infile >> count))
		throw std::exception("Failed to read ContextList.txt");
	for (unsigned i = 0; i < count; ++i)
	{
		std::string name = AttemptRead<std::string>(infile);
		std::string file = AttemptRead<std::string>(infile);
		InputContexts[name] = new InputContext(file);
	}
}

} //NS InputMapping