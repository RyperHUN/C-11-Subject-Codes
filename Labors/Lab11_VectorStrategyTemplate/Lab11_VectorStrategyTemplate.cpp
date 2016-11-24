// Lab11_VectorStrategyTemplate.cpp : Defines the entry point for the console application.
//

#include <iostream>

template <typename T>
class Vector {
private:
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
		return data[idx];
	}
};

int main() {
	Vector<int> v1(10);
}

