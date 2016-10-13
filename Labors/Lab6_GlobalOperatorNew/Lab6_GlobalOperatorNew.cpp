// Lab6_GlobalOperatorNew.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <new>
#include <iostream>

#include <cstdlib> //atexit()

#include <exception>

using namespace std;

int MEMORY_ALLOCATED = 0;

class X
{
	int i;
public:
	~X () {}
};


void * operator new(size_t sizeByte)
{
	if (sizeByte >= 1024*1024)  //Too big allocation
		throw bad_alloc{};

	void* ptr = malloc (sizeByte);

	if (ptr == nullptr)         //Failed allocation
		throw bad_alloc{};

	MEMORY_ALLOCATED += 1;

	cout << "new - Allocated " << sizeByte << " bytes at 0x" << ptr << endl;
	
	return ptr;
}



void operator delete(void * ptr) noexcept
{
	cout << "freed memory at 0x" << ptr << endl;

	MEMORY_ALLOCATED -= 1;

	free (ptr);
}

///Nem lehet destruktort hivni :(
//void operator delete[](void* ptr) noexcept
//{
//	cout << "freed memory at 0x" << ptr << endl;
//
//	int* ptrInt = (int*) ptr;
//	int length = *(ptrInt - 1);
//	for (int i = 0; i < length; i++)
//	{
//		ptrInt[i]
//	}
//	free(ptr);
//}

//void * operator new[](size_t sizeByte, size_t length)
//{
//	void* ptr = malloc(sizeByte + 4);
//	cout << "new[" << length << "] - Allocated " << sizeByte + 4 << " bytes at 0x" << ptr << endl;
//
//	return (void*) ((char*)ptr + 4);
//}

void MEMORY_HANDLER_PRINT()
{
	cout << "Remaining allocated memory:" << MEMORY_ALLOCATED << endl;
}

int main()
{
	char* c = (char*) ::operator new (10000); // Malloc writes the allocated size before it 
											  // New ugy mukodik hogy latja hogy milyen obj van mogotte es csak azt lefoglalja
											  // De ha new[] operatort hasznalsz akkor elmenti aztis hogy mennyi van,(elotte) mert neki annyit fel is kell szabaditani.
	*c = 'b';

	cout << *c << endl;

	::operator delete (c);

//Task 3

	int * num = new int; //Calls constructor too!

	delete num;

	X * intArray = new X[100];
	delete[] intArray;
	cout << "-----------------------" << endl;

//Task 4
	{
		//Bizonyos karakter alatt magaba tarolja el, bizonyos folott pedig kulon, igy gyorsabb
		//string h{"Hello vilagHvilagHello vilagHello vilagHello vilagHello vilagHello vilagHello vilagHello vilagHello vilagHello vilagHello vilagHello vilagHello vilagHello vilagHello vilagHello vilagHello vilagHello vilagHello vilag"};
		string *ptr = new string{"asd"};
		//delete ptr;
	}
	cout << "-----------------------" << endl << "Memory Leak handler" << endl;
//Task 5 Memory leak handler
	atexit(MEMORY_HANDLER_PRINT); //After exiting main it will be called
									//Test with ctrl+F5

//Task 6 adding bad alloc to new
	try
	{
		new int[1024 * 1025];
	}
	catch (bad_alloc const& failed_alloc)
	{
		cout << failed_alloc.what() << endl;
	}
	catch (exception const& e)
	{
		cout << e.what() << endl;
	}
	

#ifdef _DEBUG
	//int i;
	//std::cin >> i;
#endif
    return 0;
}

