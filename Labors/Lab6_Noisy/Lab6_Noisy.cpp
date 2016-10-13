// Lab6_Noisy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class Noisy {
public:
	explicit Noisy(int i) : i_{ i } {
		std::cout << "Noisy{" << i << "} ctor\n"; count++;
	}
	Noisy(Noisy const &o) : i_{ o.i_ } {
		std::cout << "Noisy copy ctor " << i_ << "\n"; count++;
	}
	Noisy& operator=(Noisy const &o) = delete;
	~Noisy() {
		std::cout << "Noisy dtor " << i_ << "\n"; count--;
		i_ = rand();
	}
	static void report() {
		std::cout << count << " instance(s).\n";
	}
private:
	int i_;
	static int count;
};

int Noisy::count = 0;

//T nek nincs T{} és T= sem!!!
template <typename T>
class Stack
{
	size_t size;
	size_t capacity;
	T* data;
public:
	Stack (size_t capacity = 20) 
		: capacity(capacity), size(0)
	{
		allocate ();
	}

	void push (T const& newElem)
	{
		if (size == capacity)
			throw "Stack full";

		new (data + size) T {newElem};
		size++;
	}

	T pop ()
	{
		if(size == 0)
			throw "empty stack";

		size--;
		Noisy copy = data[size];

		data[size].~T();

		return copy;
	}

	~Stack ()
	{
		::operator delete (data);
	}

	//Don't allow these
	Stack (Stack const &) = delete;
	Stack& operator=(Stack const&) = delete;

private:
	void allocate ()
	{
		data = static_cast<T*> ( ::operator new (sizeof(T) * capacity) ); // Eqvivalens malloccal!
	}

};

using namespace std;

///TODO Dynamic Stack

int main()
{
	Noisy noisy{2};
	Stack<Noisy> stack;
	stack.push (noisy);

	stack.pop ();
	
	noisy.report ();
#ifdef _DEBUG
	int i;
	std::cin >> i;
#endif
    return 0;
}

