// 4_DeclType.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <iostream>
#include "NameOfType.h"

//decltype(*begin) == int&
//auto = *begin; // Ekkor auto == int

template <typename ITER>
auto find_min(ITER begin, ITER end) -> decltype((*begin)) {
	if (begin == end)
		throw "ures";
	cout << NameOfType<decltype(*begin)>::get() << endl;
	auto min = *begin;
	while (++begin != end)
		if (*begin < min)
			min = *begin;
	return min;
}

class iterTest
{
	int data;
public:
	int& operator*() { return data; }
};

int& test(iterTest a)
{
	iterTest a2 = a;
	return *a2;
}

using namespace std;

int main()
{
	vector<int> vec = {10,2,3,1,4,5};

	cout << find_min(vec.begin(), vec.end()) << endl;

	for(int num : vec)
		cout << num << "-";
	cout << endl;

	int c = 2;
	int& cRef = c;
	auto isRef = cRef;
	isRef = 5;
	cout << isRef << "-" << c;

	test(iterTest{});

	int i;
	cin >> i;
    return 0;
}

