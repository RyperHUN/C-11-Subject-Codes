// 4_DeclType.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <iostream>
#include "NameOfType.h"

//decltype(*begin) == int&
//auto = *begin; // Ekkor auto == int


//decltype(*begin) == (T& || T const&) // Ez nek�nk nem j� hiszen a visszaadott v�ltoz� a //stacken lesz, ami a f�ggv�ny visszat�r�se ut�n megsz�nik.

//http://en.cppreference.com/w/cpp/language/auto
//(3)In a function declaration that does not use the trailing return type syntax, the //keyword auto indicates that the return type will be deduced from the operand of its //return statement using the rules for template argument deduction.

//Teh�t ha nem �rjuk ki a decltype ot akkor visszat�r�si �rt�kb�l majd kital�lja
//auto min = *begin; sorban decltype(auto) == T, �s pont ez kell nek�nk, ebb�l ki tudja //tal�lni a visszat�r�si �rt�ket.
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

