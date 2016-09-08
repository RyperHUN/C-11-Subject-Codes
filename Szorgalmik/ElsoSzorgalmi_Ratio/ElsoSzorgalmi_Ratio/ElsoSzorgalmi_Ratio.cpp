// ElsoSzorgalmi_Ratio.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>

class Ratio {       /* rational number */
public:
	Ratio(int num, int den)
	{
		/* Euclidean: gcd -> a */
		int a = num, b = den, t;
		while (b != 0)
			t = a%b, a = b, b = t;
		_num = num / a;
		_den = den / a;
	}
	int num() const { return _num; }
	int den() const { return _den; }
private:
	int _num;       /* numerator */
	int _den;       /* denominator */

public:
	//Ratio operator+(Ratio r1)
	//{
	//	return Ratio(
	//		_num * r1.den() + r1.num() * _den,
	//		r1.den() * _den);
	//}
	//Ratio& operator+=(Ratio r1)
	//{
	//	*this = Ratio(_num * r1.den() + r1.num() * _den,
	//				  r1.den() * _den);
	//	return *this;
	//}
	///// -
	//Ratio operator-(Ratio r1)
	//{
	//	return Ratio(
	//		_num * r1.den() - r1.num() * _den,
	//		r1.den() * _den);
	//}
	/////-=
	/*Ratio& operator-=(Ratio r1)
	{
		*this = Ratio(_num * r1.den() - r1.num() * _den,
				      r1.den() * _den);
		return *this;
	}*/
	/////Negalas
	Ratio operator-()
	{
		return Ratio(-1 * _num, _den);
	}
	/////*
	//Ratio operator*(Ratio r1)
	//{
	//	return Ratio (_num * r1.num (), _den * r1.den ());
	//}
	/////*=
	//Ratio& operator*=(Ratio r1)
	//{
	//	*this = Ratio(_num * r1.num(), _den * r1.den());
	//	return *this;
	//}
	/////  /
	//Ratio operator/(Ratio r1)
	//{
	//	return Ratio(_num * r1.den(), _den * r1.num());
	//}
	/////  /=
	//Ratio& operator/=(Ratio r1)
	//{
	//	*this = Ratio(_num * r1.den(), _den * r1.num());
	//	return *this;
	//}

	//friend std::istream &operator>>(std::istream &is, Ratio &r) {
	//	int num = 0, den = 0;
	//	is >> num >> den;
	//	Ratio result (num, den);
	//	r = result;

	//	return is;
	//}

	//friend std::ostream &operator<<(std::ostream &os, Ratio r) {
	//	os << r.num() << '/' << r.den();
	//	return os;
	//}
	
	operator double() const
	{
		return (double)_num / _den;
	}
};

Ratio& operator*=(Ratio &r0, Ratio r1)
{
	r0 = Ratio(r0.num() * r1.num(), r1.den() * r1.den());
	return r0;
}

Ratio& operator-=(Ratio &r0, Ratio r1)
{
	r0 = Ratio(r0.num() * r1.den() - r1.num() * r0.den(),
				  r1.den() * r0.den());;
	return r0;
}

Ratio& operator+=(Ratio &r0,Ratio r1)
{
	r0 = Ratio(r0.num() * r1.den() + r1.num() * r0.den(),
				r1.den() * r0.den());
	return r0;
}

Ratio& operator/=(Ratio &r0, Ratio r1)
{
	r0 = Ratio(r0.num() * r1.den(), r0.den() * r1.num());
	return r0;
}

Ratio operator-(Ratio r0, Ratio r1)
{
	return Ratio(
		r0.num() * r1.den() - r1.num() * r0.den(),
		r1.den() * r0.den());
}
//
Ratio operator+(Ratio r0, Ratio r1)
{
	return Ratio(
		r0.num() * r1.den() + r1.num() * r0.den(),
		r1.den() * r0.den());
}
Ratio operator*(Ratio r0, Ratio r1)
{
	return Ratio(r0.num() * r1.num(), r1.den() * r1.den());
}
/////  /
Ratio operator/(Ratio r0, Ratio r1)
{
	return Ratio(r0.num() * r1.den(), r0.den() * r1.num());
}

std::istream &operator>>(std::istream &is, Ratio &r) {
	int num = 0, den = 0;
	is >> num >> den;
	Ratio result (num, den);
	r = result;

	return is;
}

std::ostream &operator<<(std::ostream &os, Ratio r) {
	os << r.num() << '/' << r.den();
	return os;
}

int main() {
	Ratio r1(1, 10);
	Ratio r2(5, 10);
	////>> In operator test - Passed
	//Ratio r0(1,1);
	//std::cin >> r0;
	//std::cout << r0;

	///* Operator test - Passed
	Ratio result = r1 * r2;  //expected 5, 100 => 1 /20
	/// /Operator test - Passed
	Ratio result2 = r1 / r2; //Expected 1 / 5
	/// Operator += test - Passed
	Ratio result3 (1, 1); 
	result3 += r1; //Expecter 11/10
	Ratio result4(1, 1);
	Ratio finalResult = r1 + result4 += r1; //Expected 6/5
	/// Double cast - Passed
	std::cout << (double)r1 << std::endl; //expected 0.1
	/// Operator - -  Passed
	std::cout << r2 - -r1 << std::endl;  //expected 3/5 => Removing 1 operand - still works => 0.6

	Ratio r3 = r1 + r2;
	std::cout << r1 << '+' << r2 << '=' << r3 << std::endl;

#ifdef _DEBUG
	int i;
	std::cin >> i;
#endif
}

