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



int main()
{
	for (int i = 0; i < 41; i++) {
		calculatedFib[i] = fib(i);
		std::cout << "fib(" << i << ") = " << calculatedFib[i] << std::endl;
	}
    return 0;
}

