#pragma once
///TODO Maybe delete
// Dependencies
#include <istream>


//
// Helper for attempting to read from a file (or other istream-compatible interface)
//
template <typename OutType>
OutType AttemptRead(std::istream& stream)
{
	OutType out;
	if (!(stream >> out))
		throw std::exception("Failed to read a required value");

	return out;
}