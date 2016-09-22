// Lab3_SmartFloat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

const float EPSILON = 0.0001;

class Float
{
	float num;
public:
	Float (float num) :num (num) {}

	explicit operator float () const
	{
		return num;
	}
};

bool operator<(Float const& lhs, Float const& rhs)
{
	return (float)lhs < ((float)rhs - EPSILON);
}

int main()
{
	Float f1 = 1.0f,
		  f2 = 1.0001f,
		  f3 = 100;

	cout << (f1 < f2) << endl; //False!
	cout << (f1 < f3) << endl; //True!

#ifdef _DEBUG
	int i;
	cin >> i;
#endif

    return 0;
}

