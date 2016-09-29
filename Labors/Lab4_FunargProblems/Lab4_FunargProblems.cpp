// Lab4_FunargProblems.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <cmath>

class Heron
{
	double num = 0;

	bool good_enough (double guess)
	{
		return fabs (guess * guess - num) < 0.001;
	}

	double improve (double guess)
	{
		return (guess + num/guess)/2.0;
	}
public:
	double get(double x)
	{
		num = x;
		double guess = 1.0;
		while (!good_enough(guess))
			guess = improve(guess);

		return guess;
	}
};

class Derival
{
	using DoubleFunctionPtr = double (*) (double);
	DoubleFunctionPtr fv;
	double dx = 0.001;
public:
	Derival (DoubleFunctionPtr fv) 
		: fv(fv)
	{}

	double operator()(double x)
	{
		return (fv(x+dx) - fv(x)) / dx;
	}
};

int main()
{
//Downwards funargot megoldja egy valtozo, hiszen a fuggvenyeknek van *this pointere!
    Heron h;
	std::cout << h.get(2.0) << std::endl;
//Upwards funarg
	Derival my_cos = Derival{sin};
	for (double f = 0; f < 3.1415; f += 1)
		std::cout << std::setw (20) << my_cos(f) - cos(f) << std::endl; //Nagyon kicsi szam = jo!

#ifdef _DEBUG
	int i;
	std::cin >> i;
#endif
}

