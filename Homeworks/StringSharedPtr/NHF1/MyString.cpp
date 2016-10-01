#include "MyString.h"

SmartPointer::SmartPointer()
{
	ptr = nullptr;
	AllocateCounter();
}
//Move constructor
//Moves the rhs part to the lhs, and deletes rhs with nullptr
//This way in rhs destructor, it won't delete the pointers
SmartPointer::SmartPointer(SmartPointer && rhs)
{
	ptr      = rhs.ptr;
	refCount = rhs.refCount;

	rhs.ptr      = nullptr;
	rhs.refCount = nullptr;
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

	ptr      = rhs.ptr;
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

//If there is no pointer, then it wont allocate anything
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

//This will be called if we use str[i] = something
//This way the smartpointer will be reallocated ina different place, and other copies won't be modified
CharacterProxy& CharacterProxy::operator=(char rhs)
{
	ptr.ReallocateUnattached();
	ptr.get()[index] = rhs;

	return *this;
}

//Implicit char chast operator,
//This is used when we read the value of the character e.x := cout << str[i]
CharacterProxy::operator char()
{
	return ptr.get()[index];
}


String::String(const char *str /*= ""*/)
	: ptr(allocateStr(str))
{
}

//Move ctor
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
	os << str.ptr.get();  
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
	char* destString    = new char[concatLength];
	strcpy(destString, ptr.get());            //Copying lhs to destination

	strcat(destString, rhs.ptr.get());        //Copying after lhs the rhs part
	String result(destString);
	delete[] destString;

	return result;
}

String String::operator+=(const String& rhs)
{
	*this = std::move(*this + rhs); //Uses operator + this way no code duplication
									// also uses move CTOR, this way it is faster

	return *this;
}

//Comparsion operators for string
//If strcmp > 0 then lhs < rhs
//if strcmp < 0 then lhs > rhs
//if strcmp == 0 then lhs == rhs
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
