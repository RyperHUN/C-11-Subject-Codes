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


} // NS Ryper


struct Base {};

struct Derived : public Base {};

using namespace Ryper;
int main()
{
	std::cout << "IsSame test:" << std::endl;
	std::cout << "int == double " << IsSame<int,double>::value << std::endl;
	std::cout << "Base == Derived " << IsSame<Base,Derived>::value << std::endl;
	std::cout << "Base == Base " << IsSame<Base,Base>::value << std::endl;
	std::cout << std::endl << "--------------------------" << std::endl;





    return 0;
}

