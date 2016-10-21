// 5_MergeSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <memory>
#include <functional>
#include <iomanip>
#include <stdexcept>
#include <set>
#include <vector>

class Noisy {
private:
	int data;           /* csak hogy legyen-e benne valami */

						/* pÊldånyok kezelÊsÊhez */
	static std::set<Noisy const*> constructed;
	static std::set<Noisy const*> valid;
	static bool is_valid(Noisy const *n) {
		return valid.count(n) == 1;
	}
	static bool is_constructed(Noisy const *n) {
		return constructed.count(n) == 1;
	}


public:
	static bool noisy;  /* osszes ctor es dtor kiir-e kimenetre */

	int get_data() const {
		if (!is_valid(this))
			throw std::logic_error("Nem letezo objektum get_data-ja");
		return data;
	}

	Noisy(int i = 0) {
		if (is_constructed(this))
			throw std::logic_error("Letezo objektumra hivsz konstruktort");
		constructed.insert(this);
		valid.insert(this);
		data = i;
		if (noisy)
			std::cerr << "Noisy letrehozva @" << this << std::endl;
	}

	Noisy(Noisy const & o) {
		if (is_constructed(this))
			throw std::logic_error("Letezo objektumra hivsz konstruktort");
		if (!is_valid(&o))
			throw std::logic_error("Ures vagy nem letezo objektumot akarsz lemasolni");
		constructed.insert(this);
		valid.insert(this);
		data = o.data;
		if (noisy)
			std::cerr << "Noisy masolva ide @" << this << " innen @" << &o << std::endl;
	}

	Noisy(Noisy && o) {
		if (is_constructed(this))
			throw std::logic_error("Letezo objektumra hivsz konstruktort");
		if (!is_valid(&o))
			throw std::logic_error("Ures vagy nem letezo objektumot akarsz mozgatni");
		constructed.insert(this);
		valid.insert(this);
		valid.erase(&o);
		data = o.data;
		o.data = -1;
		if (noisy)
			std::cerr << "Noisy mozgatva innen @" << &o << " ide @" << this << std::endl;
	}

	~Noisy() throw (std::logic_error) { /* dtor nem kÊne dobjon, de most fog. az Êlet nem habostorta. */
		if (!is_constructed(this)) {
			throw std::logic_error("Nem letezo objektumra hivsz destruktort");
		}
		constructed.erase(this);
		valid.erase(this);
		if (noisy)
			std::cerr << "Noisy megszunt itt @" << this << std::endl;
	}

	Noisy& operator=(Noisy const &o) {
		if (!is_constructed(this))
			throw std::logic_error("Nem letezo objektum operator=-jet hivtad");
		if (!is_valid(&o))
			throw std::logic_error("Ures vagy nem letezo objektumbol akarsz erteket adni");
		data = o.data;
		if (noisy)
			std::cerr << "Noisy masolo ertekadas ide @" << this << " innen @" << &o << std::endl;
		valid.insert(this);
		return *this;
	}

	Noisy& operator=(Noisy && o) {
		if (!is_constructed(this))
			throw std::logic_error("Nem letezo objektum operator=-jet hivtad");
		if (!is_valid(&o))
			throw std::logic_error("Ures vagy nem letezo objektumbol akarsz erteket adni");
		data = o.data;
		o.data = -1;
		valid.erase(&o);
		if (noisy)
			std::cerr << "Noisy mozgato ertekadas innen @" << &o << " ide @" << this << std::endl;
		valid.insert(this);
		return *this;
	}

	static size_t get_constructed_count() {
		return constructed.size();
	}
	static size_t get_valid_count() {
		return valid.size();
	}

	friend std::ostream &operator<<(std::ostream &os, Noisy const& n);
	friend std::istream &operator >> (std::istream &is, Noisy & n);
	friend class NoisyTest;

	operator int () {return data;}
};

std::set<Noisy const*> Noisy::constructed;
std::set<Noisy const*> Noisy::valid;
bool Noisy::noisy = true;

std::ostream &operator<<(std::ostream &os, Noisy const& n) {
	if (!Noisy::is_valid(&n)) {
		throw std::logic_error("Ures vagy nem letezo objektumot akarsz kiirni");
	}
	os << n.data;
	return os;
}

std::istream &operator >> (std::istream &is, Noisy & n) {
	if (!Noisy::is_valid(&n)) {
		throw std::logic_error("Ures vagy nem letezo objektumba akarsz olvasni");
	}
	is >> n.data;
	return is;
}


template <typename T>
class MergeSorter
{
private:
	void merge(T* in, int begin, int mid, int end, T* out) {
		int i = begin, j = mid;
		for (int c = begin; c < end; ++c) {
			if (i < mid && (j >= end || in[i] <= in[j])) {
				out[c] = std::move (in[i]);
				i++;
			}
			else {
				out[c] = std::move (in[j]);
				j++;
			}
		}
	}

	void copy(T* in, int begin, int end, T* out) {
		for (int c = begin; c < end; ++c) {
			out[c] = std::move (in[c]);
		}
	}

	void merge_sort(T *tomb, int begin, int end, T *temp) {
		if (end - begin < 2)
			return;
		int mid = (begin + end) / 2;
		merge_sort(tomb, begin, mid, temp);
		merge_sort(tomb, mid, end, temp);
		merge(tomb, begin, mid, end, temp);
		copy(temp, begin, end, tomb);
	}

	T *temp;
public:

	
	void sort(T* tomb, int begin, int end)
	{
		const size_t size = end - begin;
		temp = new T[size];

		merge_sort (tomb, begin, end, temp);

		delete[] temp;
	}
};


int main()
{
	const int size = 7;
	int nums[size] = { 5, 2 , 3, 4, 6, 1, 0};

	for (auto num : nums)
		std::cout << num << " ";
	std::cout << std::endl;

	MergeSorter<int> sorterInt;
	sorterInt.sort(nums, 0, 7);

	for (auto const& num : nums)
		std::cout << num << " ";
	std::cout << std::endl;

	std::cout << "----------------------------" << std::endl;

	Noisy noisyes[size] = { 5, 2 , 3, 4, 6, 1, 0 };

	for (auto const& num : noisyes)
		std::cout << num << " ";
	std::cout << std::endl;

	MergeSorter<Noisy> sorterNoisy;
	sorterNoisy.sort(noisyes, 0, 7);

	for (auto const& num : noisyes)
		std::cout << num << " ";
	std::cout << std::endl;
	


    return 0;
}

