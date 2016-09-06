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
};

Ratio::Ratio(int num, int den) {
	/* Euclidean: gcd -> a */
	int a = num, b = den, t;
	while (b != 0)
		t = a%b, a = b, b = t;
	num_ = num / a;
	den_ = den / a;
}

Ratio operator+(Ratio r1, Ratio r2) {
	return Ratio(
		r1.num() * r2.den() + r2.num() * r1.den(),
		r1.den() * r2.den());
}

std::ostream &operator<<(std::ostream &os, Ratio r) {
	os << r.num() << '/' << r.den();
	return os;
}

int main() {
	Ratio r1(1, 10);
	Ratio r2(5, 10);
	Ratio r3 = r1 + r2;
	std::cout << r1 << '+' << r2 << '=' << r3 << std::endl;

	int i;
	std::cin >> i;
}

