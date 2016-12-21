# C-11-Subject-Codes
These repository contains all codes for C++11 subject.

Homework
=================================
1. <b>InputHandler</b> 
><p><b>Compiling</b>: Open PackageManager console, and it will automatically download the needed packages or type in : Install-Package nupengl.core </p>
> <b>Summary:</b>
> <p> This project goal was to create a robust, and really fast InputHandler.  <br/>
> It can handle XBOX controller, and Keyboard inputs really fast. You need to define actions for the inputs, wire them together and register a callback for the input device and that's it. </p>

2. <b>StringSharedPtr</b>
> <p>Simple implementation of a String which contains SharedPointer. If the string is already allocated, it will not allocate a new one, instead it shares it.</p>

Diligence
=================================
1. <b>Ratio class</b> 
><p>Create a C++ Ratio class! Needed operators: + (one operand), +=, - (1 and 2 operand), -=, *, *=, /, /=, >>, (double) cast. Use correct references. Also implement with the minimum class functions ! </p>

2. <b>Function class</b> 
> <p>Create and implement a generic Function class for the Expression Tree. Implement Sin and Cos.<br/>
> Implement derivation too. </p>

3. <b>Literal Suffix Operator - Date</b> 
	```C++
	 Date d = "2013.08.11"_date; <br/>
	 std::cout << d << std::endl;                    /* 2013.08.11. */
	 std::cout << "'99.08.11"_date << std::endl;     /* 1999.08.11. */
	 std::cout << "'12.08.11"_date << std::endl;     /* 2012.08.11. */
	 std::cout << "08.11.2013"_date << std::endl;    /* 2013.08.11. */
	```

4. <b>decltype</b>
	> Write a function template, which takes two iterators, and return the smallest element in the interval.<br/>
	> The following code is wrong, why? correct it!
	```C++
	template <typename ITER>
	auto find_min(ITER begin, ITER end) -> decltype(*begin) {
			if (begin == end)
					throw "ures";
			auto min = *begin;
			while (++begin != end)
					if (*begin < min)
							min = *begin;
			return min;
	}
	```
5. <b>Merge sort</b>
> Merge sort + Placement new

6. <b>Hanoi λ-tornyai</b>
	```C++
	#include <algorithm>
	#include <iterator>
	#include <iostream>

	void hanoi(int n, char honnan, char seged, char hova) {
			if (n == 0)
					return;
			hanoi(n-1, honnan, hova, seged);
			std::cout << "Rakd a korongot " << honnan << " oszloprol " << hova << " oszlopra\n";
			hanoi(n-1, seged, honnan, hova);
	}

	int main(void) {
			hanoi(4, 'A', 'B', 'C');
	}
	```
> Modify hanoi() function, add a fifth parameter, where we can specify a function which signature is void(char, char), it takes from -> to characters.

7. <b>print()</b>
	> Template meta programmed function. It only works with numbers, chars, and string all other types are compile time errors.
8. <b>Own std::ref</b>
	```C++
	class IntPrinter {
		private:
			int count = 0;
		public:
			void operator() (int i) {
					std::cout << ++count << ". " << i << std::endl;
			}
	};

	int arr1[] = { 5, 9, 2, 4 };
	int arr2[] = { 5, 8, 4, 7, 9 };
	IntPrinter p;
	std::for_each(std::begin(arr1), std::end(arr1), std::ref(p));     /* 1. 2. 3. 4. */
	std::for_each(std::begin(arr2), std::end(arr2), std::ref(p));     /* 5. 6. 7. 8. 9. */
	```
9. <b>Own std::function</b>
	```C++
	#include <functional>
	#include <iostream>
	#include <cmath>

	int main() {
			std::function<double(double)> f;

			if (!f)
					std::cout << "Egyelőre nullptr" << std::endl;

			f = sin;
			std::cout << sin(2.3) << "==" << f(2.3) << std::endl;

			f = [] (double x) { return x*x; };
			std::cout << 2.3*2.3 << "==" << f(2.3) << std::endl;

			f = std::bind(pow, std::placeholders::_1, 4);
			std::cout << pow(2.3, 4) << "==" << f(2.3) << std::endl;

			f = nullptr;
			try {
					f(2.3);
			} catch (std::bad_function_call &e) {
					std::cout << "Megint nullptr" << std::endl;
			}
	}
	```
10. <b>Type trait competition</b> <br/>
	*   IsClass 
	*   IsSame  : Return true if the two types are the same.
	*   IsFunction 
	*   IsArray 
	*   RemoveExtent : T[x]->T, T[x][y]->T[x]
	*   RemoveAllExtents : T[x][y]...->T
	*   ArrayDimensions  : T[x][y][z] -> 3
	*   IsPolymorphic : Returns true if class has virtual function
	*   IsEmpty : True if class is empty
	*   Decay : Applies lvalue-to-rvalue, array-to-pointer, and function-to-pointer implicit conversions to the type T, removes cv-qualifiers, and defines the resulting type as the member typedef type, Example. int const -> int, int[10] -> int*, int& -> int.
