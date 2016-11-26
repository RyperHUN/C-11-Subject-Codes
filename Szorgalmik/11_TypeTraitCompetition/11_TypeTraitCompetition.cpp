// 11_TypeTraitCompetition.cpp : Defines the entry point for the console application.
//


#include <iostream>
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
	struct isArray {
		static constexpr bool value = false;
	};
public:
	static constexpr bool value = isArray<Type>::value;
};



} // NS Ryper


struct Base {};

struct Derived : public Base {};

using namespace Ryper;
int main()
{
	std::cout << "IsArray test:" << std::endl;
	std::cout << "int "  << IsArray<int>::value << std::endl;
	std::cout << "int[] "<< IsArray<int[]>::value << std::endl;
	std::cout << "int* " << IsArray<int*>::value << std::endl;
	//std::cout << IsArray<int[][]>::value << std::endl; // Not works :(
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

