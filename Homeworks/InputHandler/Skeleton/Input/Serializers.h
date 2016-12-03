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
	std::ofstream file(fileName);
	mapWriter(ranges, file);
	mapWriter(states, file);
	mapWriter(actions, file);

	///TODO Sensitivity + Conversions
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

void pugXmlTest()
{
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("cd_catalog.xml");

	std::cout << "Load result: " << result.description() << std::endl;

	for (auto catalog : doc.children("CATALOG"))
	{
		for (auto cd : catalog.children("CD"))
		{
			std::cout << "CD - ";

			for (auto attr : cd.attributes())
			{
				std::cout << " " << attr.name() << "=" << attr.value();
			}

			for (pugi::xml_node child : cd.children())
			{
				std::cout << ", child " << child.name() << "val=" << child.first_child().value();
			}
			std::cout << std::endl;
		}
	}
}

} //NS InputMapp