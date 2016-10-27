// Lab8_Stack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "stack.h"
#include <iostream>
#include <cstdlib>
#include <new>
#include <stdexcept>


template <typename T>
class Stack {
public:
	explicit Stack(size_t max_size);
	Stack(Stack const &orig);
	Stack & operator=(Stack const &orig) = delete;
	~Stack();
	void push(T const &what);
	T pop();
	bool empty() const;
private:
	size_t size_;
	size_t max_size_;
	T *pData_;
};

template <typename T>
Stack<T>::Stack(size_t max_size) {
	size_ = 0;
	max_size_ = max_size;
	//pData_ = (T*)malloc(sizeof(T) * max_size_); //Not handling bad_alloc
	pData_ = (T*) ::operator new(sizeof(T) * max_size_);
}


template <typename T>
Stack<T>::Stack(Stack<T> const &orig) {
	size_ = orig.size_;
	max_size_ = orig.max_size_;
	pData_ = ::operator new(sizeof(T) * max_size_);
	size_t i = 0
		try {
		for (i = 0; i != size_; ++i)
			new (&pData_[i]) T{ orig.pData_[i] };
	}
	catch (...) {
		while (i != unsigned(-1))
		{
			i--;
			pData_[i].~T();
		}
	}
}


template <typename T>
Stack<T>::~Stack() {
	for (size_t i = 0; i != size_; ++i)
		pData_[i].~T();
	::operator delete(pData_);
}


/* Push element onto stack. */
template <typename T>
void Stack<T>::push(T const &what) {
	size_++;
	new (&pData_[size_ - 1]) T{ what };
}


/* Pop element from top of the stack. */
template <typename T>
T Stack<T>::pop() {
	size_--;
	T saved{ pData_[size_] };
	pData_[size_].~T();
	return saved;
}


template <typename T>
bool Stack<T>::empty() const {
	return size_ == 0;
}

int main() {
	Stack<char> s{ 100 };
	char c;
	while (std::cin.get(c))
		s.push(c);
	while (!s.empty())
		std::cout << s.pop();
}

