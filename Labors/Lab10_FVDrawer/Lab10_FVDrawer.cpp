// Lab10_FVDrawer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

class Page {
public:
	Page(int w, int h) : w_(w), h_(h), page_(w*h) {
		clear();
	}

	void clear() {
		std::fill(page_.begin(), page_.end(), ' ');
	}

	void print() const {
		for (int y = 0; y < h_; ++y) {
			for (int x = 0; x < w_; ++x)
				std::cout << page_[y*w_ + x];
			std::cout << std::endl;
		}
	}

	void setchar(int x, int y, char c) {
		if (x >= 0 && x < w_ && y >= 0 && y < h_)
			page_[y*w_ + x] = c;
	}

	int get_width() const {
		return w_;
	}

	int get_height() const {
		return h_;
	}

private:
	int w_, h_;
	std::vector<char> page_;
};

///Faster compile
void plot(Page &p, char c, std::function<double(double)> f) {
	for (int x = 0; x < p.get_width(); ++x) {
		double fx = (x - p.get_width() / 2.0) / 4.0;
		double fy = f(fx);
		int y = -(fy * 4.0) + p.get_height() / 2;
		p.setchar(x, y, c);
	}
}
///Faster Run Time
//template <typename T>
//void plot(Page &p, char c, T f) {
//	for (int x = 0; x < p.get_width(); ++x) {
//		double fx = (x - p.get_width() / 2.0) / 4.0;
//		double fy = f(fx);
//		int y = -(fy * 4.0) + p.get_height() / 2;
//		p.setchar(x, y, c);
//	}
//}

int main() {
	Page p(75, 20);

	plot(p, '#', static_cast<double(*)(double)>(std::sin)); //sin X
	//plot(p, 'x', static_cast<double(*)(double)>(std::cos)); //cos X

	int n = 2;
	plot(p, '$', [n](double x){ return std::sin(x * n);} ); //sin n*x
	p.print();
}

/// STD::SIN = Magic overloaded function type
// std::sin(float), std::sin (double), std::sin(long double)...
/// CHoose : static_cast<double(*)(double)>

