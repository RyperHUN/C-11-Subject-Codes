// Lab7_RAII_ImproveWithMove.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>

/* FILE* RAII */
class FilePtr {
public:
	FilePtr () 
		: fp_{nullptr}
	{
	}
	explicit FilePtr(const char * fileName, const char* mode) 
		: fileName_ {fileName} 
	{
		fp_ = fopen (fileName, mode);
		if (fp_ == nullptr)
			throw "failed to open";
	}
	~FilePtr() {
		close_if_open();
	}
	/* nem másolható */
	FilePtr(FilePtr const &) = delete;
	FilePtr & operator=(FilePtr const &) = delete;
	//Move CTOR
	FilePtr (FilePtr && rhs)
	{
		fileName_ = std::move(rhs.fileName_);
		fp_       = rhs.fp_;
		rhs.fp_   = nullptr;
	}
	FilePtr& operator= (FilePtr && rhs)
	{
		if (this != &rhs)
		{
			close_if_open ();
			fileName_ = std::move(rhs.fileName_);
			fp_       = rhs.fp_;
			rhs.fp_   = nullptr;
		}

		return *this;
	}


	operator FILE* () const {
		return fp_;
	}
private:
	FILE *fp_;
	std::string fileName_;

	void close_if_open() {
		if (fp_ != nullptr)
			fclose(fp_);
		fp_ = nullptr;
	}
};

FilePtr open_for_writing(char const *name) {
	return FilePtr{ name, "wt" };
}


/* ne lehessen ilyet csinálni (az operator FILE* miatt lehetne) */
void fclose(FilePtr) = delete;


int main() {
	//FilePtr fpOld{ "hello.txt", "wt" };

	FilePtr fp;
	fp = open_for_writing("hello.txt");
	fprintf(fp, "Hello vilag");
	fp = open_for_writing("hello2.txt");
	fprintf(fp, "Hello vilag");
}

