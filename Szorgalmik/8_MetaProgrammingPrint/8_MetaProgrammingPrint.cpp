// 8_MetaProgrammingPrint.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"

#include <type_traits>
#include <iostream>

template <typename T>
struct IsNumber {
	static constexpr bool value = false;
};

template <>
struct IsNumber<int> {
	static constexpr bool value = true;
};

template <>
struct IsNumber<double> {
	static constexpr bool value = true;
};

template <>
struct IsNumber<float> {
	static constexpr bool value = true;
};


template <typename T>
typename std::enable_if<IsNumber <T>::value>::type 
print (T val)
{
	std::cout << val << " ";
}

//print <typename T>
//typename std::enable_if<std::is


	
int main()
{
	std::cout << "Number test:" << std::endl;
	print (5);
	print (5.1);
	print (5.1f);

	std::cout << std::endl << "";


    return 0;
}

