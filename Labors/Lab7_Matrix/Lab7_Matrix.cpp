// Lab7_Matrix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <cassert>
#include <iostream>

class Matrix {
private:
	size_t w_, h_;
	double *data_;
public:
	size_t getW () {return w_;}
	size_t getH () {return h_;}

	Matrix () 
		: w_(0), h_(0), 
		  data_ (nullptr)
	{}

	Matrix (size_t w, size_t h) 
		: w_(w), h_(h)
	{
		data_ = (double*) malloc (sizeof (double) * (w_ * h_) );
		bejar ( [](double& x) { x = 0;});
	}

	double& operator()(size_t sor, size_t oszlop) // i,j
	{
		assert (sor < h_ && oszlop < w_);

		return data_ [sor * w_ + oszlop];
	}

	double& operator()(size_t sor, size_t oszlop) const // i,j
	{
		assert(sor < h_ && oszlop < w_);

		return data_[sor * w_ + oszlop];
	}

	
	void bejar (void (*fv)(double&))
	{
		for (size_t i = 0; i < w_ * h_ ; i++)
		{
			fv (data_[i]);
		}
	}
};

std::ostream& operator<<(std::ostream &os, Matrix m)
{
	for (size_t i = 0 ; i < m.getH (); i++)
	{
		for (size_t j = 0; j < m.getW (); j++)
		{
			os << m (i, j) << "  ";
		}
		os << std::endl;
	}
	return os;
}

int main()
{
	Matrix m{ 3, 3 };
	m(0, 0) = 9;  m(2, 1) = 5;
	std::cout << m;

    return 0;
}

