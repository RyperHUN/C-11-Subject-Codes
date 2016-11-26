// 11_TypeTraitCompetition.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include "NameOfType.h"
#include <iterator>
#include <vector>
#include <list>
using Vector = std::vector<int>/*::iterator*/;
using List = std::list<int>::iterator;

namespace Ryper {

template <typename T>
class IsClass {
private:
	template <typename U>
	static constexpr bool helper(int U::*) { return true; }

	template <typename U>
	static constexpr bool helper(...) { return false; }

public:
	static constexpr bool value = helper<T>(0);
};

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

	template <typename RET, size_t SIZE>
	struct isArray<RET[SIZE]> {
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

//-ArrayDimensions<T>::value: a tömb dimenzióinak száma, pl.T[x][y][z] esetén 3.

template <typename Type>
class ArrayDimensions {
private:
	template <typename T>
	struct arrayDimensions;

	template <typename T>
	struct arrayDimensions {
		static constexpr int value = 0;
	};

	template <typename T>
	struct arrayDimensions<T[]> {
		static constexpr int value = 1;
	};

	template <typename T, size_t SIZE>
	struct arrayDimensions<T[SIZE]> {
		static constexpr int value = 1 + arrayDimensions<T>::value;
	};
public:
	static constexpr int value = arrayDimensions<Type>::value;
};

//-IsIterable<T>::value: megeszi - e az std::begin() függvény.

template<typename T>
struct HasFunction
{
	template<typename U, size_t(U::*)() const> struct SFINAE {};
	template<typename U> static char Test(SFINAE<U, &U::begin>*);
	template<typename U> static int Test(...);
	static const bool value = sizeof(Test<T>(0)) == sizeof(char);
};

template <typename ITER>
class IsIterable {
public:
	static constexpr bool val2 = HasFunction<ITER>::value;
	static constexpr bool value = IsArray <ITER>::value || val2;
	
};

//-HasRandomAccessIterator<T>::value: mint az elõzõ, de az is feltétel, hogy random access iterálható legyen.

template <typename ITER>
class HasRandomAccessIterator {
public:
	template <typename T>
	static constexpr bool IsRandomAccess() {
		/*typename std::iterator_traits<ITER>::iterator_category tag;*/
		return IsSame<std::random_access_iterator_tag, typename std::iterator_traits<T>::iterator_category>::value;
	}
	//template <typename T>
	//static constexpr bool IsRandomAccess(...) {
	//	return true;
	//}
	static constexpr int value = IsIterable<ITER>::value && IsRandomAccess<ITER> ();
};

//-IsEmptyClass<T>::value: igaz, ha üres a T osztály, nincs adattagja, pl. struct X {}.
template <typename T>
struct IsEmpty {
	static constexpr bool value = IsClass<T>::value && sizeof(T) == 1; // sizeof(Empty) class always == 1
};

///////////////////////////////////////////////////////////////////////
//template <typename T>
//struct IsEnum {
//	static constexpr bool value = false;
//};
//
//template <>
//struct IsEnum<enum> {
//	static constexpr bool value = true;
//};
//template <typename T>
//class IsEnum {
//private:
//	template <typename U>
//	static constexpr bool helper(int U::*) { return true; }
//
//	template <typename U>
//	static constexpr bool helper(...) { return false; }
//
//	enum Another {
//		EnumVal
//	};
//
//public:
//	static constexpr bool value = IsSame<Another,T>::value;
//};
///////////////////////////////////////////////////////////////////////

//-IsAbstract<T>::value
//template <typename T>
//class IsAbstract {
//private:
//	template <typename U>
//	static constexpr bool helper(int ) { return false; }
//
//	template <typename U>
//	static constexpr bool helper(...) { return true; }
//
//public:
//	static constexpr bool value = helper<T>(0);
//};
/////////////////////////////////////////////////////////////////////////

//-Decay<T>::type: a benne lévõ típus a T típus függvényparaméter átadáskori transzformáltja, pl. int const -> int, int[10] -> int*, int& -> int.
template <typename TYPE>
class Decay {
private:
	template <typename T>
	struct decay;

	template <typename T, size_t S>
	struct decay<T[S]> {
		using type = T*;
	};

	template <typename T>
	struct decay {
		using type = T;
	};

	template <typename T>
	struct decay<T&> {
		using type = T;
	};

	template <typename T>
	struct decay<T&&> {
		using type = T;
	};

	template <typename T>
	struct decay<const T> {
		using type = T;
	};

	template <typename T>
	struct decay<const T&> {
		using type = T;
	};

	template <typename RET, typename ...ARGS>
	struct decay<RET(ARGS...)> {
		using type = RET(*)(ARGS...);
	};
public:
	using type = typename decay<TYPE>::type;
};

} // NS Ryper


struct Base {};

struct Derived : public Base {};

class AbstractClass {
public:
	virtual void abstractFv() = 0;
};

struct Empty {};
struct NotEmpty { int i; };

enum EnumType {
	EnumValue
};


template <typename T, typename U>
struct decay_equiv :
	Ryper::IsSame<typename Ryper::Decay<T>::type, U>
{};


using namespace Ryper;
int main()
{
	std::cout << "IsDecay test:" << std::endl;
	std::cout << std::boolalpha
		<< decay_equiv<int, int>::value << std::endl
		<< decay_equiv<int&, int>::value << std::endl
		<< decay_equiv<int&&, int>::value << std::endl
		<< decay_equiv<const int&, int>::value << std::endl
		<< decay_equiv<int[2], int*>::value << std::endl
		<< decay_equiv<int(int), int(*)(int)>::value << std::endl;
	std::cout << std::endl << "--------------------------" << std::endl;

	//std::cout << "IsAbstract test:" << std::endl;
	//std::cout << "Empty => " << IsAbstract<Empty>::value << std::endl;
	//std::cout << "AbstractClass => " << IsAbstract<AbstractClass>::value << std::endl;
	//std::cout << std::endl << "--------------------------" << std::endl;

	/*std::cout << "IsEnum test:" << std::endl;
	std::cout << "Empty => " << IsEnum<Empty>::value << std::endl;
	std::cout << "EnumType => " << IsEnum<EnumType>::value << std::endl;
	std::cout << std::endl << "--------------------------" << std::endl;*/

	std::cout << "IsEmpty test:" << std::endl;
	std::cout << "Empty => "    << IsEmpty<Empty>::value << std::endl;
	std::cout << "NotEmpty => " << IsEmpty<NotEmpty>::value << std::endl;
	std::cout << std::endl << "--------------------------" << std::endl;

	//std::begin ()
	std::cout << "HasRandomAccessIterator test:" << std::endl;
	//std::cout << "int[] => " << HasRandomAccessIterator<int[]>::value << std::endl;
	//std::cout << "VectorIt => " << HasRandomAccessIterator<Vector>::value << std::endl;
	//std::cout << "ListIt => " << HasRandomAccessIterator<List>::value << std::endl;
	std::cout << std::endl << "--------------------------" << std::endl;

	std::cout << "IsIterable test:" << std::endl;
	std::cout << "int[2] => " << IsIterable<int[2]>::value << std::endl;
	std::cout << "VectorIt => " << IsIterable<Vector>::value << std::endl;
	std::cout << "ListIt => " << IsIterable<List>::value << std::endl;
	std::cout << std::endl << "--------------------------" << std::endl;

	std::cout << "ArrayDimensions test:" << std::endl;
	std::cout << "int[] => " << ArrayDimensions<int[]>::value << std::endl;
	std::cout << "int[2][3] => " << ArrayDimensions<int[2][3]>::value << std::endl;
	std::cout << "int[3][6][19][20] => " << ArrayDimensions<int[3][6][19][20]>::value << std::endl;
	//std::cout << "int[3][6][19][20] => " << NameOfType<RemoveAllExtents<int[3][6][19][20]>::type>::get() << std::endl;
	std::cout << std::endl << "--------------------------" << std::endl;

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

