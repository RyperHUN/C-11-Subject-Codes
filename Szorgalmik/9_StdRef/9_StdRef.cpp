// 9_StdRef.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <type_traits>
//#include <algorithm>

class IntPrinter {
private:
	int count = 0;
public:
	void operator() (int i) {
		std::cout << ++count << ". " << i << std::endl;
	}

	void operator() (int &&i, int b) {
		std::cout << ++count << ". " << i << " RVALUE!!!" << std::endl;
	}
};

template< class T >
class reference_wrapper {
	static_assert (std::is_class<T>::value, "Only accepts Objects");
	T& _val;
public:
	reference_wrapper (T &val)
		:_val (val) {}

	/*operator T& () {return _val;}*/
	template< class... Types>
	void operator() (Types &&... types) {
		_val (std::forward<Types>(types)...);
	}
};

template <typename T>
reference_wrapper<T> ref (T& val)
{
	return reference_wrapper<T>(val);
}

template<class InputIt, class UnaryFunction>
UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f)
{
	for (; first != last; ++first) {
		f(*first);
	}
	return f;
}



int main()
{
	int arr1[] = { 5, 9, 2, 4 };
	int arr2[] = { 5, 8, 4, 7, 9 };
	IntPrinter p;
	reference_wrapper<IntPrinter> wrappedIntPrinter = ref (p);
	//ref (1); // Compile time error

	//wrappedIntPrinter (); // Compile time error
	wrappedIntPrinter (1, 2);
	wrappedIntPrinter (2);
	for_each(std::begin(arr1), std::end(arr1), ref(p));     /* 1. 2. 3. 4. */
	for_each(std::begin(arr2), std::end(arr2), p);     /* 5. 6. 7. 8. 9. */

    return 0;
}

