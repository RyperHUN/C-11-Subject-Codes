// ElsoSzorgalmi_Ratio.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>

class Ratio {       /* rational number */
public:
	Ratio(int num, int den);
	int num() const { return num_; }
	int den() const { return den_; }
private:
	int num_;       /* numerator */
	int den_;       /* denominator */

public:
	Ratio operator+(Ratio r1)
	{
		return Ratio(
			num_ * r1.den() + r1.num() * den_,
			r1.den() * den_);
	}
	Ratio& operator+=(Ratio r1)
	{
		*this = *this + r1;
		return *this;
	}
	///Egyoperandusu -
	//Ratio operator-(Ratio r1)
	//{
	//	return Ratio(
	//		num_ * r1.den() + r1.num() * den_,
	//		r1.den() * den_);
	//}
	///-=
	///*
	Ratio operator*(Ratio r1)
	{
		return Ratio (num_ * r1.num (), den_ * r1.den ());
	}
	///*=
	///  /
	Ratio operator/(Ratio r1)
	{
		return Ratio(num_ * r1.den(), den_ * r1.num());
	}
	///  /=
	

	friend std::istream &operator>>(std::istream &is, Ratio &r) {
		int num = 0, den = 0;
		is >> num >> den;
		Ratio result (num, den);
		r = result;

		return is;
	}

	friend std::ostream &operator<<(std::ostream &os, Ratio r) {
		os << r.num() << '/' << r.den();
		return os;
	}

	/// (double) cast
};

Ratio::Ratio(int num, int den) {
	/* Euclidean: gcd -> a */
	int a = num, b = den, t;
	while (b != 0)
		t = a%b, a = b, b = t;
	num_ = num / a;
	den_ = den / a;
}

//Ratio operator+(Ratio r1, Ratio r2) {
//	return Ratio(
//		r1.num() * r2.den() + r2.num() * r1.den(),
//		r1.den() * r2.den());
//}

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
	
	Ratio r3 = r1 + r2;
	std::cout << r1 << '+' << r2 << '=' << r3 << std::endl;

#ifdef _DEBUG
	int i;
	std::cin >> i;
#endif
}

