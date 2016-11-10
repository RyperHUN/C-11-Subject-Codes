// Lab10_Transform.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>

double doubler (double x)
{
	return x *2;
}

int main() {
	{
		std::vector<double> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		std::function<double(double)> SQRT = static_cast<double(*)(double)>(sqrt); // If type is not valid, COMPILE TIME ERROR!!
		std::transform(v.begin(), v.end(), v.begin(), SQRT);

		for (auto i : v)
			std::cout << i << std::endl;
	}
	std::cout << "---------------------" << std::endl;
	{
		std::vector<double> v = { 1, 2, 3, 4 };

		int inputNum = 3;

		//std::transform(v.begin(), v.end(), v.begin(), doubler);
		//std::transform (v.begin(), v.end (), v.begin (), [](int x){return x *2;});
		std::transform (v.begin(), v.end (), v.begin (), [inputNum](int x){return x *inputNum;});

		for (auto i : v)
			std::cout << i << std::endl;
	}
	std::cout << "---------------------" << std::endl;
	std::cout << "With std::multiplies + std::bind" << std::endl;
	{
		std::vector<double> v = { 1, 2, 3, 4 };

		int inputNum = 3;

		auto inputNumMultiplier = std::bind (std::multiplies<int>{}, std::placeholders::_1, inputNum);
		//std::transform(v.begin(), v.end(), v.begin(), [inputNum](int x) {return std::multiplies<int>{} (x, inputNum); });
		std::transform(v.begin(), v.end(), v.begin(), [inputNumMultiplier](int x) {return inputNumMultiplier (x);});

		for (auto i : v)
			std::cout << i << std::endl;
	}

}
