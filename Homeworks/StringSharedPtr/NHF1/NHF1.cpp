// NHF1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstring>
#include <iostream>
#include <memory>

using namespace std;

class SmartPointer final{
public:
	//Ctors
	SmartPointer ()
	{
		ptr = nullptr;
		AllocateCounter ();
	}
	//Explicittel nem fog minden pointert egybol SmartPointerre castolni
	explicit SmartPointer(char* pointer) ///TODO It can be called after constructor call with = but why??
		: ptr{ pointer }
	{
		AllocateCounter();
	}
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

	/////TODO
	//char* operator* ()
	//{
	//	return ptr;
	//}
	

private:
	//Releases pointers if reference counter is equals 0
	void Release()
	{
		(*refCount)--;        //Decrements refcount
		if (*refCount == 0)   //If no more reference to the pointer, deletes it
		{
			delete[] ptr;
			ptr = nullptr;
			delete refCount;
			refCount = nullptr; //nullptr makes it more safe
		}
	}
	void AllocateCounter()
	{
		if (ptr)
		{
			refCount = new unsigned int; //Allocates memory for shared reference counter
			*refCount = 0;
			(*refCount)++;
		}
		else
			refCount = nullptr;
	}

	unsigned int* refCount; //it is a pointer, so it can be shared between smartPointers
	char*         ptr;
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
///TODO Sok komment minden fuggvenyhez!

class String 
{
	size_t size;   //str len + 1 ('\0')
	//SmartPointer<char> ptr;
	SmartPointer ptr;
public:
	String (const char *str = "")
		: ptr (allocateStr (str))
	{
	}

	String (String&& str)
	{
		
	}

	String (String &rhs)
		: ptr (rhs.ptr), size (rhs.size)
	{
	}
	String& operator= (String const& rhs)
	{
		size = rhs.size;
		ptr  = rhs.ptr;      //Deletes this string reference to the allocated memory 
							//Sets new ref to the rhs's ref
		///TODO Maybe remove reference increasing from = and add ptr.IncrementRef function -> This way we can move the ptr

		return *this;       //allows str = str2 = str3;
	}
	//Copies parameter to a newly allocated char*
	char* allocateStr (const char* str)
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

	friend ostream& operator<< (ostream &os, String const& str)
	{
		os << str.ptr.get ();  ///TODO * operator not works
		return os;
	}

	friend istream& operator>> (istream &is, String& str)
	{
		const size_t BUFFERSIZE = 200;
		char* word              = new char[BUFFERSIZE];
		//is.getline (word, sizeof(word));
		is >> word;

		///This way leak!!
		//str.ptr = str.allocateStr (word);
		String newStr {word};
		str = newStr;

		delete[] word;

		return is;
	}
	String operator+(const String& rhs)
	{
		size_t concatLength = size + rhs.size - 1; // -1 because we only need 1 '\0' terminating null
		char* destString = new char [concatLength];
		strcpy (destString, ptr.get());

		strcat (destString, rhs.ptr.get ());
		String result(destString);
		delete[] destString;

		return result;
	}
	String operator+=(const String& rhs)
	{
		*this = *this + rhs;

		return *this;
	}

	bool operator<(String const& rhs) const
	{
		return strcmp(ptr.get(), rhs.ptr.get()) > 0;
	}
	bool operator>(String const& rhs) const
	{
		return strcmp(ptr.get(), rhs.ptr.get()) < 0;
	}
	bool operator==(String const& rhs) const
	{
		return strcmp(ptr.get(), rhs.ptr.get()) == 0;
	}
};

template <typename T>
struct TreeElement
{
	T* elem;
	TreeElement* left;
	TreeElement* right;
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
		cout << "Operator[] teszt" << endl;
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
	{
		cout << "Operator +/+= test" << endl;
		String left ("left");
		String right ("right");
		cout << "+ expected :" << endl << "leftright" << endl;
		cout << left + right << endl;

		left += right;
		cout << "+= expected :" << endl << "leftright" << endl;
		cout << left << endl;
	}
	cout << "-------------------------------" << endl;
	{
		cout << "Operator </==/> test" << endl;
		String left("a");
		String right("b");
		String same("a");
		cout << "< expected :" << endl << "a" << endl;
		if( left < right)
			cout << left << endl;

		cout << "== expected :" << endl << "a" << endl;
		if( left == same)
			cout << same << endl;
	}
	cout << "-------------------------------" << endl;
	{ //Operator >>
		cout << "Operator >> test" << endl;
		String reading{"DELETE ME PLEASE"};
		cin >> reading;
		cout << reading;

	}
	/*String a, b, c;
	c = "Hello vilag";*/


	int i;
	cin >> i;
    return 0;
}

