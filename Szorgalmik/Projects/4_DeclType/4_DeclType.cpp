// 4_DeclType.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <iostream>
#include "NameOfType.h"

//decltype(*begin) == int&
//auto = *begin; // Ekkor auto == int


//decltype(*begin) == (T& || T const&) // Ez nekünk nem jó hiszen a visszaadott változó a //stacken lesz, ami a függvény visszatérése után megszûnik.

//http://en.cppreference.com/w/cpp/language/auto
//(3)In a function declaration that does not use the trailing return type syntax, the //keyword auto indicates that the return type will be deduced from the operand of its //return statement using the rules for template argument deduction.

//Tehát ha nem írjuk ki a decltype ot akkor visszatérési értékbõl majd kitalálja
//auto min = *begin; sorban decltype(auto) == T, és pont ez kell nekünk, ebbõl ki tudja //találni a visszatérési értéket.
//IF c++14 >= 
//template <typename ITER>
//auto find_min (ITER begin, ITER end)


template <typename ITER>
auto find_min(ITER begin, ITER end) -> decltype(*begin) {
	if (begin == end)
		throw "ures";

	ITER minIter = begin;
	while (++begin != end)
		if (*begin < *minIter)
			minIter = begin;

	return *minIter;
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

