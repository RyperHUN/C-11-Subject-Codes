// Lab10_Transform.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
	std::vector<double> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	//std::function<double(double)> SQRT = sqrt;
	//std::transform(v.begin(), v.end(), v.begin(), sqrt);

	for (auto i : v)
		std::cout << i << std::endl;
}
