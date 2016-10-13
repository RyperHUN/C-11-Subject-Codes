// 4_DeclType.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <iostream>

template <typename ITER>
auto find_min(ITER begin, ITER end) -> decltype(*begin) {
	if (begin == end)
		throw "ures";
	decltype(*begin) min = *begin;
	while (++begin != end)
		if (*begin < min)
			min = *begin;
	return min;
}

using namespace std;

int main()
{
	vector<int> vec = {10,2,3,1,4,5};

	cout << find_min(vec.begin(), vec.end());


	int i;
	cin >> i;
    return 0;
}

