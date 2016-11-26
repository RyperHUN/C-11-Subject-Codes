// 11_TypeTraitCompetition.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include "NameOfType.h"

namespace Ryper {

template <typename T, typename T2>
class IsSame {
private:
	
	template <typename Type>
	struct Helper {
		static constexpr bool helper(...) { return false; }
	};

	template <>
	struct Helper<T> { 
		static constexpr bool helper(...) { return true; }
	};

public:
	static constexpr bool value = Helper<T2>::helper();
};



//IsFunction<T>::value: függvény - e, pl. int(bool) függvény, mert int f(bool);
template <typename FUNCTION>
struct IsFunction {
	template <typename FUNC>
	class isFunction;

	template <typename RET, typename ... ARGS>
	class isFunction<RET(ARGS...)> {
	private:

	public:
		static constexpr bool value = true;
	};

	template <typename FUNC>
	class isFunction {
	public:
		static constexpr bool value = false;
	};

	static constexpr bool value = isFunction<FUNCTION>::value;
};

template <typename Type>
class IsArray {
private:
	template <typename FUNC>
	struct isArray;

	template <typename RET>
	struct isArray<RET[]> {
		static constexpr bool value = true;
	};

	template <typename RET>
	struct isArray<RET*[]> {
		static constexpr bool value = true;
	};

	template <typename RET>
	struct isArray {
		static constexpr bool value = false;
	};
public:
	static constexpr bool value = isArray<Type>::value;
};

template <typename T>
class RemoveExtent {
private:
	template <typename Type>
	struct removeExtent;

	template <typename Type, size_t SIZE>
	struct removeExtent<Type[SIZE]>
	{
		using type = Type;
	};

	template <typename Type>
	struct removeExtent<Type[]> //Empty => int[]
	{
		using type = Type;
	};
public:
	using type = typename removeExtent<T>::type;
};

//RemoveAllExtents<T>::type: az összes dimenziót leveszi : T[x][y]...->T, amúgy általában T->T.

template <typename Type>
class RemoveAllExtents {
private:
	template <typename T>
	struct removeAllExtents;

	template <typename T>
	struct removeAllExtents {
		using type = T;
	};

	template <typename T, size_t SIZE>
	struct removeAllExtents<T[SIZE]> {
		using type = typename removeAllExtents<T>::type;
	};
public:
	using type = typename removeAllExtents<Type>::type;
};

} // NS Ryper


struct Base {};

struct Derived : public Base {};

using namespace Ryper;
int main()
{
	std::cout << "RemoveALLExtent test:" << std::endl;
	std::cout << "int[2][3] => " << NameOfType<RemoveAllExtents<int[2][3]>::type>::get () << std::endl;
	std::cout << "int[3][6][19][20] => " << NameOfType<RemoveAllExtents<int[3][6][19][20]>::type>::get() << std::endl;
	//std::cout << "int[]" << NameOfType<RemoveAllExtents<int[]>::type>::get() << std::endl;
	std::cout << std::endl << "--------------------------" << std::endl;
	std::cout << "RemoveExtent test:" << std::endl;
	std::cout << "int[2] =>" << NameOfType<RemoveExtent<int[2]>::type>::get () << std::endl;
	std::cout << "int[2][3] =>" << NameOfType<RemoveExtent<int[2][3]>::type>::get() << std::endl;
	std::cout << std::endl << "--------------------------" << std::endl;
	std::cout << "IsArray test:" << std::endl;
	std::cout << "int "    << IsArray<int>::value << std::endl;
	std::cout << "int[] "  << IsArray<int[]>::value << std::endl;
	std::cout << "int* "   << IsArray<int*>::value << std::endl;
	std::cout << "int[][]" << IsArray<int[2][3]>::value << std::endl; // Not works :(
	std::cout << std::endl << "--------------------------" << std::endl;
	std::cout << "IsFunction test:" << std::endl;
	std::cout << "int test: " << IsFunction<int>::value <<std::endl;
	std::cout << "int () test: " << IsFunction<int()>::value << std::endl;
	std::cout << std::endl << "--------------------------" << std::endl;
	std::cout << "IsSame test:" << std::endl;
	std::cout << "int == double " << IsSame<int,double>::value << std::endl;
	std::cout << "Base == Derived " << IsSame<Base,Derived>::value << std::endl;
	std::cout << "Base == Base " << IsSame<Base,Base>::value << std::endl;
	std::cout << std::endl << "--------------------------" << std::endl;





    return 0;
}

