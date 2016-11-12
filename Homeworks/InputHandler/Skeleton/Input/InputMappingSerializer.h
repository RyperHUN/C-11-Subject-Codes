#pragma once
#include "InputMapper.h"
#include "../ThirdParty/pugixml.hpp"

namespace InputMapping {

class InputMapperSerializer
{
public:
	static void Serialize(InputMapping::InputMapper & inputMapper) {
		//For All contexts
		auto firstElem = inputMapper.InputContexts.begin();
		InputMapping::InputContext* elem = firstElem->second;
		/*inputMapper.InputContexts()*/
	}
};


} // NS InputMapping