// 8_MetaProgrammingPrint.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"

#include <type_traits>
#include <iostream>
#include <string>

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
struct IsChar {
	static constexpr bool value = false;
};

template <>
struct IsChar<char> {
	static constexpr bool value = true;
};

template <>
struct IsChar<char16_t> {
	static constexpr bool value = true;
};

template <typename T>
struct IsString {
	static constexpr bool value = false;
};

template <>
struct IsString<const char*> {
	static constexpr bool value = true;
};

template <>
struct IsString<std::string> {
	static constexpr bool value = true;
};



template <typename T>
typename std::enable_if<IsNumber <T>::value>::type 
print (T val)
{
	std::cout << val << " ";
}

//typename std::enable_if<std::_Is_character<T>::value>::type
///std::_is_character nem mukodik char_16t re

template <typename T>
typename std::enable_if<IsChar<T>::value>::type
print(T val)
{
	std::cout << "'" << val << "' ";
}

template <typename T>
typename std::enable_if<IsString<T>::value>::type
print(T val)
{
	std::cout << "\"" << val << "\" ";
}


//print <typename T>
//typename std::enable_if<std::is


	
int main()
{
	std::cout << "Number test:" << std::endl;
	print (5);
	print (5.1);
	print (5.1f);

	std::cout << std::endl << std::endl << "Char test:" << std::endl;
	print('c');
	print(static_cast<char16_t>('b'));
	
	std::cout << std::endl << std::endl <<"String test:" << std::endl;

	print("Easy game");
	std::string str("test");
	print(str);


    return 0;
}

