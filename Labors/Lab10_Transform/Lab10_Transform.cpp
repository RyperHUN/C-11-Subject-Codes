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
		std::function<double(double)> SQRT = static_cast<double(*)(double)>(sqrt);
		std::transform(v.begin(), v.end(), v.begin(), SQRT);

		for (auto i : v)
			std::cout << i << std::endl;
	}
	std::cout << "---------------------" << std::endl;
	{
		std::vector<double> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		//std::transform(v.begin(), v.end(), v.begin(), doubler);
		std::transform (v.begin(), v.end (), v.begin (), [](int x){return x *2;});

		for (auto i : v)
			std::cout << i << std::endl;
	}

}
