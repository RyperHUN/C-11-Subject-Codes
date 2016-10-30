#pragma once
#include <cmath>
#include "Math4.h"

#include <cassert>

namespace Math {

class Vec4 {
public:
	float v[4];

	Vec4(float x = 0, float y = 0, float z = 0, float w = 0) {
		v[0] = x; v[1] = y; v[2] = z; v[3] = w;
	}

	Vec4(const Vec4 &rhs) {
		for (int i = 0; i < 4; i++)
			v[i] = rhs.v[i];
	}

	Vec4& operator=(Vec4 &rhs) {
		if (this == &rhs)
			return *this;

		for (int i = 0; i < 4; i++)
			v[i] = rhs.v[i];

		return *this;
	}
	Vec4 operator*(const float skalar) const
	{
		Vec4 result;
		for (int i = 0; i < 4; i++)
			result.v[i] = v[i] * skalar;
		return result;
	}
	Vec4& operator*=(const float skalar)
	{
		for (int i = 0; i < 4; i++)
			v[i] = v[i] * skalar;
		
		return *this;
	}

	Vec4 operator+(const Vec4& right) const
	{                                 
		Vec4 result;
		for (int i = 0; i < 4; i++)
			result.v[i] = right.v[i] + v[i];

		return result;
	}
	Vec4& operator+=(const Vec4& rhs)
	{
		for (int i = 0; i < 4; i++)
			v[i] += rhs.v[i];

		return *this;
	}

	Vec4 operator-(const Vec4& right)
	{
		return Vec4(v[0] - right.v[0], v[1] - right.v[1], v[2] - right.v[2], v[3] - right.v[3]);
	}

	//Negate
	Vec4 operator-() const
	{
		return Vec4(v[0] * -1, v[1] * -1, v[2] * -1, v[3] * -1);
	}

	Vec4& operator-=(const Vec4& right)
	{
		for (int i = 0; i < 4 ; i++)
			v[i] -= right.v[i];

		return *this;
	}

	///Divide by 0???
	Vec4 operator/(const float& right) const
	{
		Vec4 eredmeny;

		Vec4 uj(v[0] / right, v[1] / right, v[2] / right, v[3] / right);
		eredmeny = uj;

		return eredmeny;
	}

	Vec4 operator/=(const float& right)
	{
		*this = *this / right;

		return *this;
	}



	float length() const
	{
		return sqrtf(v[0] * v[0] + v[1] * v[1]);
	}

	float& operator[](int index) {
		assert(0 <= index && index <= 3 && "Vec4/Color : Not valid index");

		return v[index];
	}

	float operator[](int index) const {
		assert (0 <= index && index <= 3 && "Vec4/Color : Not valid index");

		return v[index];
	}


	Vec4 operator*(const Mat4& rhs) const {
		Vec4 result;
		for (int i = 0; i < 4; ++i) {
			// Columns
			float value = 0.0f;
			for (int j = 0; j < 4; ++j) {
				value += v[j] * rhs[4 * i + j];
			}
			result.v[i] = value;
		}
		return result;
	}
};

Vec4 operator*(const float szam,const Vec4& right)
{
	return right * szam;
}


// Jobbrol szorzas vektorral // Vektor jobbrol matrix
Vec4 Mat4::operator*(const Vec4& right) const
{
	Vec4 result;
	for (int i = 0; i < 4; i++) {
		result.v[i] = 0;
		for (int j = 0; j < 4; j++) {

			result.v[i] += m[4 * i + j] * right.v[j];
		}
	}
	return result;
}


} //namespace Math
