// Lab6_GlobalOperatorNew.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <new>
#include <iostream>

using namespace std;

void * operator new(size_t size)
{
	void* ptr = malloc (size);
	cout << "Allocated " << size << " bytes at 0x" << ptr << endl;
	
	return ptr;
}

void operator delete(void * ptr) noexcept
{
	cout << "freed memory at 0x" << ptr << endl;
	free (ptr);
}

int main()
{
	char* c = (char*) ::operator new (1);
	*c = 'b';

	cout << *c << endl;

	::operator delete (c);


#ifdef _DEBUG
	int i;
	std::cin >> i;
#endif
    return 0;
}

