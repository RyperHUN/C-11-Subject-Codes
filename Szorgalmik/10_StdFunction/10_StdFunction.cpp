// 10_StdFunction.cpp : Defines the entry point for the console application.
//


#include <functional>
#include <iostream>
#include <cmath>

int main() {
	std::function<double(double)> f;

	if (!f)
		std::cout << "Egyelore nullptr" << std::endl;

	f = static_cast<double(*)(double)>(sin);
	std::cout << sin(2.3) << "==" << f(2.3) << std::endl;

	f = [](double x) { return x*x; };
	std::cout << 2.3*2.3 << "==" << f(2.3) << std::endl;

	f = std::bind(static_cast<double(*)(double,int)>(pow), std::placeholders::_1, 4);
	std::cout << pow(2.3, 4) << "==" << f(2.3) << std::endl;

	f = nullptr;
	try {
		f(2.3);
	}
	catch (std::bad_function_call &e) {
		std::cout << "Megint nullptr" << std::endl;
	}
}

