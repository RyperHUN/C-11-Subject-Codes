#include "MyString.h"

SmartPointer::SmartPointer()
{
	ptr = nullptr;
	AllocateCounter();
}
SmartPointer::SmartPointer(SmartPointer && str)
{
	ptr = str.ptr;
	refCount = str.refCount;

	str.ptr = nullptr;
	str.refCount = nullptr;
}
//Explicittel nem fog minden pointert egybol SmartPointerre castolni
SmartPointer::SmartPointer(char* pointer)
	: ptr{ pointer }
{
	AllocateCounter();
}
SmartPointer::SmartPointer(SmartPointer &rhs)
	: ptr{ rhs.ptr }, refCount{ rhs.refCount }
{
	(*refCount)++; //Increments reference counter
}

SmartPointer& SmartPointer::operator= (SmartPointer const& rhs)
{
	Release(); //Releases the current reference

	ptr = rhs.ptr;
	refCount = rhs.refCount;
	(*refCount)++; //One more pointer to the data, need to increment counter!

	return *this;  //This way we can do things like this ptr = ptr2 = ptr3
}



SmartPointer::~SmartPointer()
{
	Release();
}

void SmartPointer::ReallocateUnattached()
{
	char* ptrNew = new char[strlen(ptr) + 1];
	strcpy(ptrNew, ptr);
	Release();
	ptr = ptrNew;
	AllocateCounter();
}

char* const SmartPointer::get() const    //Pointer can't be modified, but it's value can!
{
	return ptr;
}

//Releases pointers if reference counter is equals 0
void SmartPointer::Release()
{
	if (ptr != nullptr)
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
}
void SmartPointer::AllocateCounter()
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


CharacterProxy::CharacterProxy(SmartPointer & ptr, size_t index)
	:ptr(ptr), index(index)
{}

CharacterProxy& CharacterProxy::operator=(char rhs)
{
	ptr.ReallocateUnattached();
	ptr.get()[index] = rhs;

	return *this;
}

CharacterProxy::operator char()
{
	return ptr.get()[index];
}


String::String(const char *str /*= ""*/)
	: ptr(allocateStr(str))
{
}

String::String(String&& str)
	: ptr(std::move(str.ptr)), size(str.size)
{
}

String::String(String &rhs)
	: ptr(rhs.ptr), size(rhs.size)
{
}
String& String::operator= (String const& rhs)
{
	size = rhs.size;
	ptr = rhs.ptr;      //Deletes this string reference to the allocated memory 
						//Sets new ref to the rhs's ref

	return *this;       //allows str = str2 = str3;
}
//Copies parameter to a newly allocated char*
char* String::allocateStr(const char* str)
{
	size = strlen(str) + 1; //string length includes '\0'
	char* newStr = new char[size];
	strcpy(newStr, str);
	return newStr;
}

String::~String()
{
	size = 0;
}

size_t String::Size() const { return size; }

char const& String::operator[] (size_t index) const
{
	return ptr.get()[index];
}

CharacterProxy String::operator[] (size_t index)
{
	//Prohibits modifications with non const String
	return CharacterProxy{ ptr, index };
}

ostream& operator<< (ostream &os, String const& str)
{
	os << str.ptr.get();  ///TODO * operator not works
	return os;
}

istream& operator >> (istream &is, String& str)
{
	const size_t BUFFERSIZE = 200;
	char* word = new char[BUFFERSIZE];
	is >> word;

	///This way leak!!
	//str.ptr = str.allocateStr (word);
	String newStr{ word };
	str = std::move(newStr);

	delete[] word;

	return is;
}
String String::operator+(const String& rhs)
{
	size_t concatLength = size + rhs.size - 1; // -1 because we only need 1 '\0' terminating null
	char* destString = new char[concatLength];
	strcpy(destString, ptr.get());

	strcat(destString, rhs.ptr.get());
	String result(destString);
	delete[] destString;

	return result;
}
String String::operator+=(const String& rhs)
{
	*this = *this + rhs;

	return *this;
}

bool String::operator<(String const& rhs) const
{
	return strcmp(ptr.get(), rhs.ptr.get()) > 0;
}
bool String::operator>(String const& rhs) const
{
	return strcmp(ptr.get(), rhs.ptr.get()) < 0;
}
bool String::operator==(String const& rhs) const
{
	return strcmp(ptr.get(), rhs.ptr.get()) == 0;
}
