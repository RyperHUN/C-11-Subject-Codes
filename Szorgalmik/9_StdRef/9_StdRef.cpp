// 9_StdRef.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <algorithm>

class IntPrinter {
private:
	int count = 0;
public:
	void operator() (int i) {
		std::cout << ++count << ". " << i << std::endl;
	}
};



int main()
{
	int arr1[] = { 5, 9, 2, 4 };
	int arr2[] = { 5, 8, 4, 7, 9 };
	IntPrinter p;
	std::for_each(std::begin(arr1), std::end(arr1), std::ref(p));     /* 1. 2. 3. 4. */
	std::for_each(std::begin(arr2), std::end(arr2), std::ref(p));     /* 5. 6. 7. 8. 9. */

    return 0;
}

