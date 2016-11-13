#pragma once
#include "InputMapper.h"
#include "HighLevelInputConstants.h"
#include "../ThirdParty/pugixml.hpp"
#include <iostream>

namespace InputMapping {

//template <typename InputType>
//class InputMapperSerializer
//{
//public:
//	void CreateContext (std::map<InputType, Range> const& ranges,
//						std::map<InputType, State> const& states,
//						std::map<InputType, Action> const& actions,
//						RawGamePadInputToString converter
//						/*Sensitivity*/
//						)
//	{
//		InputMapping::RangeToString rangeToStrConverter;
//		pugi::xml_document doc;
//		pugi::xml_node MainNode = doc.append_child("Context");
//		pugi::xml_node RangesNode = MainNode.append_child("Ranges");
//		for (auto range : ranges) {
//			pugi::xml_node Range = RangesNode.append_child("Range");
//			pugi::xml_node key = Range.append_child ("Key");
//			std::string str = converter[range.first];
//			key.append_child(pugi::node_pcdata).set_value(str.c_str ());
//			pugi::xml_node value = Range.append_child("Value");
//			std::string str2 = rangeToStrConverter[range.second];
//			value.append_child (pugi::node_pcdata).set_value (str2.c_str());
//		}
//
//		doc.print(std::cout);
//	}
//	void Serialize(InputMapping::InputMapper<InputType> & inputMapper) {
//		//For All contexts
//		auto firstElem = inputMapper.InputContexts.begin();
//		InputMapping::InputContext<inputType>* elem = firstElem->second;
//		/*inputMapper.InputContexts()*/
//	}
//};

template <typename InputType>
void contextCreator (std::string fileName,
					std::map<InputType, Range> ranges,
					std::map<InputType, State>  states,
					std::map<InputType, Action> actions/*,
					std::map<Range, double> sensitivity,
					std::map<InputType, Action> conversion*/
					)
{
	std::ofstream file (fileName); ///TODO Error handling
	mapWriter (ranges, file);
	mapWriter (states, file);
	mapWriter (actions, file);

	file << 0 << std::endl; // Sensitivity
	file << 0 << std::endl; // COnversions
}
template <typename InputType, typename ActionType>
static void mapWriter (std::map<InputType,ActionType> map, std::ofstream& file)
{
	file << map.size() << std::endl;
	for (auto elem : map) {
		file << elem.first << " " << elem.second << std::endl;
	}
}

} // NS InputMapping