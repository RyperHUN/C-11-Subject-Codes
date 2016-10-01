#pragma once
#ifndef MYSTRING_H
#define MYSTRING_H

#include <cstring>
#include <iostream>

using namespace std;

class SmartPointer final {
public:
	//Ctors
	SmartPointer();

	SmartPointer(SmartPointer && str);

	//Explicittel nem fog minden pointert egybol SmartPointerre castolni
	explicit SmartPointer(char* pointer);

	SmartPointer(SmartPointer &rhs);

	SmartPointer& operator= (SmartPointer const& rhs);

	~SmartPointer();

	void ReallocateUnattached();

	char* const get() const;    //Pointer can't be modified, but it's value can!

private:
	//Releases pointers if reference counter is equals 0
	void Release();


	void AllocateCounter();

	unsigned int* refCount; //it is a pointer, so it can be shared between smartPointers
	char*         ptr;
};

class CharacterProxy {
private:
	SmartPointer& ptr;
	size_t index;
public:
	CharacterProxy(SmartPointer & ptr, size_t index);

	CharacterProxy& operator=(char rhs);

	operator char();
};

class String
{
	size_t size;   //str len + 1 ('\0')
				   //SmartPointer<char> ptr;
	SmartPointer ptr;
public:
	String(const char *str = "");

	String(String&& str);

	String(String &rhs);

	String& operator= (String const& rhs);

	//Copies parameter to a newly allocated char*
	char* allocateStr(const char* str);

	~String();

	size_t Size() const;

	char const& operator[] (size_t index) const;

	CharacterProxy operator[] (size_t index);

	String operator+(const String& rhs);

	String operator+=(const String& rhs);


	bool operator<(String const& rhs) const;

	bool operator>(String const& rhs) const;

	bool operator==(String const& rhs) const;

	friend ostream& operator<< (ostream &os, String const& str);


	friend istream& operator >> (istream &is, String& str);
};



#endif //MYSTRING_H