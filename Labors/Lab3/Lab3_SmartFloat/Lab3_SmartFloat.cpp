// Lab3_SmartFloat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

const float EPSILON = 0.00001f;

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
//Osszehasonlitok
bool operator<(Float const& lhs, Float const& rhs)
{
	return (float)lhs < ((float)rhs - EPSILON);
}

bool operator!=(Float const& lhs, Float const& rhs)
{
	return rhs < lhs || lhs < rhs;
}

bool operator==(Float const& lhs, Float const& rhs)
{
	return !(lhs != rhs);
}

bool operator<=(Float const& lhs, Float const& rhs)
{
	return lhs == rhs || lhs < rhs;
}

bool operator>(Float const& lhs, Float const& rhs)
{
	return !(lhs <= rhs);
}

bool operator>=(Float const& lhs, Float const& rhs)
{
	return lhs == rhs || lhs > rhs;
}

//Osszehasonlito vege
////////////////////////////////////////////////////////////////

Float operator+(Float const& lhs)
{
	return Float(lhs);
}
Float operator-(Float const& lhs)
{
	return Float(-1*(float)lhs);
}

Float operator+(Float const& lhs, Float const& rhs)
{
	return Float((float)lhs + (float)rhs);
}

Float& operator+=(Float& lhs, Float const& rhs)
{
	lhs = lhs + rhs;
	return lhs;
}

Float operator-(Float const& lhs, Float const& rhs)
{
	return Float((float)lhs - (float)rhs);
}

Float& operator-=(Float& lhs, Float const& rhs)
{
	lhs = lhs - rhs;
	return lhs;
}

ostream& operator<<(ostream& os, Float const& rhs)
{
	os << (float)rhs;
	return os;
}

int main()
{
	Float f1 = 1.0f,
		  f2 = 1.0001f,
		  f3 = 100;

	cout << (f1 < f2) << endl; //False!
	cout << (f1 < f3) << endl; //True!

	f1 = f2 + f3;

	for (Float f = 0.999; f < 1.001; f += 0.0001){
		cout << f << '\t' << (f < 1.0) << std::endl;
	}

	cout << -f1;

	//Futasideju koltseg??
#ifdef _DEBUG
	int i;
	cin >> i;
#endif

    return 0;
}

