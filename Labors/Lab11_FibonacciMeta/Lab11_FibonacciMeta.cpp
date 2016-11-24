// Lab11_FibonacciMeta.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <map>

std::map<int,int> calculatedFib;

int fib (int n) {
    if (n < 2)
		return n;

	auto elem = calculatedFib.find(n);
	if (elem != calculatedFib.end ())
		return (*elem).second;

	return fib (n - 2) + fib (n-1);
}


template <int N>
struct Fib {
	static constexpr int value = Fib<N-1>::value + Fib<N-2>::value;
};

template <>
struct Fib<0> {
	static constexpr int value = 0;
};
template <>
struct Fib<1> {
	static constexpr int value = 1;
};


int main()
{
	/*for (int i = 0; i < 41; i++) {
		calculatedFib[i] = fib(i);
		std::cout << "fib(" << i << ") = " << calculatedFib[i] << std::endl;
	}*/

	std::cout << Fib<40>::value << std::endl;
    return 0;
}

