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
	size_t getW () const {return w_;}
	size_t getH () const {return h_;}

	Matrix () 
		: w_(0), h_(0), 
		  data_ (nullptr)
	{}

	Matrix (Matrix const& rhs)
	{
		std::cout << "Copy CTOR" << std::endl;
		w_ = rhs.getW();
		h_ = rhs.getH();
		data_ = (double*)malloc(sizeof(double) * (w_ * h_));
		for (size_t i = 0; i < w_ * h_; i++)
		{
			data_[i] = rhs.data_[i];
		}
	}
	// Move CTOR
	Matrix (Matrix && rhs)
	{
		std::cout << "Move CTOR" << std::endl;

		w_ = rhs.getW();
		h_ = rhs.getH();
		data_	  = rhs.data_;
		rhs.data_ = nullptr;
	}

	Matrix& operator=(Matrix const& rhs)
	{
		if (this != &rhs)
		{
			if (data_ != nullptr)
				free (data_);

			w_ = rhs.getW();
			h_ = rhs.getH();
			data_ = (double*)malloc(sizeof(double) * (w_ * h_));
			for (size_t i = 0; i < w_ * h_; i++)
			{
				data_[i] = rhs.data_[i];
			}
		}

		return *this;
	}

	Matrix& operator=(Matrix && rhs)
	{
		std::cout << "Move =" << std::endl;
		if (this != &rhs)
		{
			if (data_ != nullptr)
				free(data_);

			w_ = rhs.getW();
			h_ = rhs.getH();
			data_ = rhs.data_;
		}

		return *this;
	}


	Matrix (size_t h, size_t w)
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
	std::cout << m << std::endl;

	Matrix copyMtx = m;
	std::cout << copyMtx;

	std::swap(copyMtx, m);

    return 0;
}

