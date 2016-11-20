#pragma once
#include "InputMapper.h"
#include "HighLevelInputConstants.h"
#include "../ThirdParty/pugixml.hpp"
#include <iostream>

namespace InputMapping {

	//Serializer beta

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

} // NS InputMapping