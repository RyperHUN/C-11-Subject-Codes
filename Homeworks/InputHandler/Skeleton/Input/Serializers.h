#pragma once

#include "HighLevelInputConstants.h"
#include <fstream>
#include <map>

namespace InputMapping {

template <typename InputType>
void ContextCreator(std::string fileName,
	std::map<InputType, Range> ranges,
	std::map<InputType, State>  states,
	std::map<InputType, Action> actions
	/*,
	std::map<Range, double> sensitivity,
	std::map<InputType, Action> conversion*/
	)
{
	std::ofstream file(fileName); ///TODO Error handling
	mapWriter(ranges, file);
	mapWriter(states, file);
	mapWriter(actions, file);

	file << 0 << std::endl; // Sensitivity
	file << 0 << std::endl; // COnversions
}

template <typename InputType, typename ActionType>
static void mapWriter(std::map<InputType, ActionType> map, std::ofstream& file)
{
	file << map.size() << std::endl;
	for (auto elem : map) {
		file << elem.first << " " << elem.second << std::endl;
	}
}

} //NS InputMapping