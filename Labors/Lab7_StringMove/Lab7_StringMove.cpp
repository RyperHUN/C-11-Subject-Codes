// Lab7_StringMove.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class String {
public:
	char *data;
public:
	String(String &&);
	String (char* str) 
	{
		data = str;
	}
};

String::String(String && the_other) {
	/*data = static_cast<char* &&> (the_other.data);*/
	/*data = std::move(the_other.data);*/
	data = the_other.data; // szebb
	the_other.data = nullptr;
}

int main()
{
	char * szoveg = "asddd";
	
	String test = szoveg;
	String moved = std::move(test);
	
	std::cout << moved.data;

    return 0;
}

