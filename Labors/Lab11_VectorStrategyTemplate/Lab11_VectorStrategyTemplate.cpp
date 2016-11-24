// Lab11_VectorStrategyTemplate.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <type_traits>

struct Strategy {

};

template <typename T>
struct IsStrategy {
	static constexpr bool value = false;
};

template <>
struct IsStrategy <Strategy> {
	static constexpr bool value = true;
};

//Maybe static asser + is base of
template <
	      typename T, 
		  class StrategyType /*,
		  typename Dummy     = typename std::enable_if< IsStrategy<StrategyType>::value>::type*/  //Only accepts Strategy
		 > 
class Vector {
private:
	static_assert (std::is_base_of <Strategy, StrategyType>::value, "Only accepts Strategy types");
	size_t size;
	T* data;

public:
	Vector(size_t size)
		: size{ size }
		, data{ new T[size] } {
	}
	Vector(Vector const &) = delete; /* lusta */
	Vector& operator=(Vector const &) = delete; /* lusta */
	~Vector() {
		delete[] data;
	}

	T& operator[](size_t idx) {
		StrategyType::IndexChecker (*this, size, idx);

		return data[idx];
	}
};

class StrategyNull : Strategy
{
public:
	template <typename T>
	static void IndexChecker(Vector<T, StrategyNull>& /*vec*/, size_t /*size*/, size_t /*index*/) {}
};

class StrategyException : Strategy
{
public:
	template <typename T>
	static void IndexChecker(Vector<T, StrategyException>& vec, size_t size, size_t index) {
		if (size <= index)
			throw std::out_of_range("size is bigger than index");
	}
};

int main() {
	try {
		//Vector<int,int> test(10);
		Vector<int, StrategyNull> v1(10);
		v1 [11]; // Nothing
		Vector<int, StrategyException> vExc (10);
		vExc [11];
	} catch (std::exception exc) {
		std::cout << "ERROR " << exc.what() << std::endl;
	}
}

