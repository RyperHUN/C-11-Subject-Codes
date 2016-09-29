// Lab4_RAII_UnmanagedResource.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdio>

//Shared pointernek a konstruktoraba meglehet adni felszabaditot
class FilePtr
{
	FILE* file = nullptr;
	int *refCount;
public:
	FilePtr () 
	{
		refCount = new int;
		*refCount = 0;
	}
	FilePtr (FILE* file) : file(file) 
	{
		refCount = new int;
		*refCount = 1;
	}

	operator FILE* ()
	{
		return file;
	}

	~FilePtr ()
	{
		(*refCount)--;
		if(*refCount == 0)
		{
			delete refCount;
			if (file != nullptr)
				fclose (file);
		}
	}

	FilePtr& operator=(FilePtr const& rhs)
	{
		refCount = rhs.refCount;
		(*refCount)++;
		file = rhs.file;

		return *this;
	}
	FilePtr(FilePtr const& rhs)
	{
		*this = rhs;
	}
};

int main()
{
	{
		FilePtr fp;
		fp = fopen("hello2.txt", "wt");
		fprintf(fp, "Hello Vilag");
	}
#ifdef _DEBUG
	int i;
	std::cin >> i;
#endif
    return 0;
}

