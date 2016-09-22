// Lab3_LiteralStringConversion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

///FONTOS ATVENNI A MERETET!
std::string operator"" _s(const char* str, size_t size)
{
	return std::string (str, size); //Fontos hogy a meretet megkapja a konstruktor, kulonben az elso lezaro nullaig fogja kiirni!
}

int main()
{
    std::cout << "Hello"_s + " vilag" << std::endl; //Hello vilag
	std::cout << "hello\0vilag"_s.length () << std::endl;

#ifdef _DEBUG
	int i;
	std::cin >> i;
#endif
	return 0;
}

