// Lab11_OwnIsBaseOf.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <type_traits>
//Original std::is_base_of <Strategy, StrategyType>::value

//Easier version
//template <typename Base, typename Derived>
//struct is_base_of {
//	static constexpr bool value = std::is_convertible<Derived, Base>::value ? true : false;
//};

template <typename Base, typename Derived>
struct is_base_of {

	static constexpr bool helper (void *) { return false; }
	static constexpr bool helper (Base *) { return true; }

	static constexpr bool value = helper ((Derived*)nullptr);
};

class Base {};
class Derived : public Base {};

int main() {
	std::cout << is_base_of<Base, Derived>::value;    /* 1 */
	std::cout << is_base_of<Base, std::ostream>::value;    /* 0 */
}


