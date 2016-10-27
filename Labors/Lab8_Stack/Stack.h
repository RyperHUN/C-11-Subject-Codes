#pragma once


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