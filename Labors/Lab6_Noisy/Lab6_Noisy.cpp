// Lab6_Noisy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class Noisy {
public:
	explicit Noisy(int i) : i_{ i } {
		std::cout << "Noisy{" << i << "} ctor\n"; count++;
	}
	Noisy(Noisy const &o) : i_{ o.i_ } {
		std::cout << "Noisy copy ctor " << i_ << "\n"; count++;
	}
	Noisy& operator=(Noisy const &o) = delete;
	~Noisy() {
		std::cout << "Noisy dtor " << i_ << "\n"; count--;
		i_ = rand();
	}
	static void report() {
		std::cout << count << " instance(s).\n";
	}
private:
	int i_;
	static int count;
};

int Noisy::count = 0;

int main()
{


    return 0;
}

