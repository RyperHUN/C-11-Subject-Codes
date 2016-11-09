// 6_LambdaHanoi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <algorithm>
#include <iterator>
#include <iostream>

class FvTor {
public:
	FvTor () {}
	
	void operator () (char a, char b)
	{
		std::cout << "Rakd a korongot " << a << " oszloprol " << b << " oszlopra\n";
	}
};

template <typename T>
void hanoi (int n, char honnan, char seged, char hova, T fv)
{
	if (n == 0)
		return;
	hanoi (n - 1, honnan, hova, seged, fv);
	fv (honnan, hova);
	hanoi (n - 1, seged, honnan, hova, fv);
}

int main (void)
{
	hanoi (4, 'A', 'B', 'C', FvTor{});
	return 0;
}
