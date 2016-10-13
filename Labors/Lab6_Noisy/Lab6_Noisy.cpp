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
		data = allocate (capacity);
	}

	void push (T const& newElem)
	{
		if (size == capacity)
			multiplyCapacity (2);

		new (data + size) T {newElem}; //Placement new - Only calls T Copy CTOR!!
		size++;
	}

	T pop ()
	{
		if (size == 0)
			throw "empty stack";
		
		size--;
		Noisy copy = data[size];
		data[size].~T();    //Only calls T Destructor

		if (size < capacity / 4)
			divideCapacity (2);

		return copy;
	}

	~Stack ()
	{
		callDestructors ();
		deleteMemory ();
	}

	//Don't allow these
	Stack (Stack const &) = delete;
	Stack& operator=(Stack const&) = delete;

private:
	T* allocate (size_t howBig)
	{
		return static_cast<T*> ( ::operator new (sizeof(T) * howBig) ); // Eqvivalens malloccal!
	}

	void multiplyCapacity (int increaseBy)
	{
		capacity = capacity * increaseBy;
		modifyCapacity (capacity);
	}

	void divideCapacity (int decraseBy)
	{
		capacity = capacity / decraseBy;
		modifyCapacity (capacity);
	}

	void modifyCapacity (int capacity)
	{
		T* newData = allocate(capacity);  //Alloc new container for data

		for (size_t i = 0; i < size; i++)  //Copy existing data
		{
			new (newData + i) T{ data[i] }; //Calls newData[i] CopyCtor
		}

		callDestructors();
		deleteMemory();

		//Set new ptr for this->data
		data = newData;
	}

	void callDestructors ()
	{
		//Call Dtor for old members
		for (size_t i = 0; i < size; i++)
		{
			data[i].~T();
		}
	}

	void deleteMemory ()
	{
		//Delete old ptr
		::operator delete(data); // == free(data), no DTOR call
	}
};

using namespace std;

int main()
{
	{
		Noisy noisy{2};
		Stack<Noisy> stack {10};
		stack.push (noisy);
		stack.push (Noisy{4}); //Doubling size if stackCap == 1
		cout << "------------" << endl;
		stack.pop (); //shrink capacity by 2
	
		Noisy::report ();
	}
	Noisy::report ();
#ifdef _DEBUG
	int i;
	std::cin >> i;
#endif
    return 0;
}

