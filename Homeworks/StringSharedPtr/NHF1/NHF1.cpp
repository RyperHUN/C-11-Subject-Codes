// NHF1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstring>
#include <iostream>
#include <memory>

using namespace std;

///TODO - Maybe char kent kellene letrehozni es az egesz struktura jo a get fuggveny adna vissza a teljes ptr-t
//template <typename T>
//class SmartPointer 
//{
//	unsigned int _refCount;
//public:
//	T* _pointer;
//public:
////Ctors
//	SmartPointer () = delete;
//
//	SmartPointer (T* pointer)
//		: _pointer{pointer}
//	{
//	}
//
//	~SmartPointer ()
//	{
//		_refCount--;        //Decrements refcount
//		if (_refCount == 0) //If no more reference to the pointer, deletes it
//			delete _pointer;
//	}
//
//	T& operator* ()
//	{
//		return _pointer;
//	}
//
//	T* operator-> ()
//	{
//		return _pointer;
//	}
//};

class SmartPointer final{
	unsigned int* refCount; //it is a pointer, so it can be shared between smartPointers
	char* ptr;  

private:

	void Release ()
	{
		(*refCount)--;        //Decrements refcount
		if (*refCount == 0)   //If no more reference to the pointer, deletes it
		{
			delete ptr;
			ptr = nullptr;
			delete refCount;
			refCount = nullptr; //nullptr makes it more safe
		}
	}
	void AllocateCounter ()
	{
		refCount  = new unsigned int; //Allocates memory for shared reference counter
		*refCount = 0;
		(*refCount)++;
	}
public:
	//Ctors
	SmartPointer () = delete; 
	SmartPointer (SmartPointer &rhs)
		: ptr {rhs.ptr}, refCount {rhs.refCount}
	{
		(*refCount)++; //Increments reference counter
	}

	SmartPointer& operator= (SmartPointer const& rhs)
	{
		Release (); //Releases the current reference

		ptr  = rhs.ptr;
		refCount = rhs.refCount;
		(*refCount)++; //One more pointer to the data, need to increment counter!

		return *this;  //This way we can do things like this ptr = ptr2 = ptr3
	}

	SmartPointer (char* pointer)
		: ptr{pointer}
	{
		AllocateCounter ();
	}

	~SmartPointer ()
	{
		Release ();
	}

	void ReallocateUnattached ()
	{
		char* ptrNew = new char[strlen(ptr) + 1];
		strcpy (ptrNew, ptr);
		Release ();
		ptr = ptrNew;
		AllocateCounter ();
	}

	char* const get () const    //Pointer can't be modified, but it's value can!
	{
		return ptr;
	}

	///TODO
	char* operator* ()
	{
		return ptr;
	}
};

class CharacterProxy {
private:
	SmartPointer& ptr;
	size_t index;
public:
	CharacterProxy (SmartPointer & ptr, size_t index)
		:ptr (ptr), index (index)
	{}

	CharacterProxy& operator=(char rhs)
	{
		ptr.ReallocateUnattached ();
		ptr.get ()[index] = rhs;

		return *this;
	}
	operator char ()
	{
		return ptr.get ()[index];
	}
};

///TODO Mozgato konstruktor
///String összefûzés +, +=
///TODO Sok komment minden fuggvenyhez!

///TODO szorgalmi Kereso fa
class String 
{
	size_t size;   //str len + 1 ('\0')
	//SmartPointer<char> ptr;
	SmartPointer ptr;
public:
	String (const char *str = "")
		: ptr (initStr (str))
	{
	}

	String (String &rhs)
		: ptr (rhs.ptr), size (rhs.size)
	{
	}
	String& operator= (String const& rhs)
	{
		size = rhs.size;
		ptr = rhs.ptr;      //Deletes this string reference to the allocated memory 
							//Sets new ref to the rhs's ref

		return *this;       //allows str = str2 = str3;
	}

	char* initStr (const char* str)
	{
		size  = strlen (str) + 1; //string length includes '\0'
		char* newStr = new char[size];
		strcpy (newStr, str);
		return newStr;
	}

	~String ()
	{
		size = 0;
	}
	size_t Size () const { return size; }

	char const& operator[] (size_t index) const
	{
		return ptr.get ()[index];
	}

	CharacterProxy operator[] (size_t index)
	{
		//Prohibits modifications with non const String
		return CharacterProxy {ptr, index};
	}

	friend ostream& operator<< (ostream &os, String& str)
	{
		os << str.ptr.get ();  ///TODO * operator not works
		return os;
	}

	friend istream& operator>> (istream &is, String& str)
	{
		char* readLine = nullptr;
		//is.getline (readLine, sizeof(readLine));
		is >> readLine;
		str.ptr = readLine;
		str.size = strlen (readLine + 1);

		return is;
	}
};



int main()
{
	{
		String empty{}; //Letrehoz uresen
		cout << empty;
		cout << "Init teszt";
		String init {"hello vilag - Init Teszt + Copy"};

		cout << init << endl;

		//Copy with reference counting
		{
			String a = init;
			cout << a << endl;
		}
		String b ("Release Teszt");
		cout << b << endl;
		b = init;   //= operator works, copies the rhs and releases lhs
		cout << b << endl;
	}
	cout << "-------------------------------" << endl;

	{
		cout << "Operator[] teszt";
		String normal {"ab"};
		String const constCopy = normal;
		String normalCopy = normal;
		cout << "Const expected :" << endl << "a - ab" << endl;
		//operatorCopy[0] = 'c'; const works cannot modify
		cout << constCopy[0] << " - " << normal << endl; //Write is allowed
		normalCopy[0] = 'c';
		cout << "Not Const expected :" << endl << "c - ab" << endl;
		cout << normalCopy[0] << " - " << normal << endl;
	}

	cout << "-------------------------------" << endl;

	{ //Operator >>
		cout << "Operator >> test" << endl;
		String reading;
		cin >> reading;
		cout << reading;

	}
	/*String a, b, c;
	c = "Hello vilag";*/


	int i;
	cin >> i;
    return 0;
}

