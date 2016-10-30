#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <cassert>

namespace Math {
class Vec4;


///TODO Maybe generic Matrix class with initializer list;

struct Mat4 {
private:

	/// http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
	static bool gluInvertMatrix(const float m[16], float invOut[16])
	{
		float inv[16], det;
		int i;

		inv[0] = m[5] * m[10] * m[15] -
			m[5] * m[11] * m[14] -
			m[9] * m[6] * m[15] +
			m[9] * m[7] * m[14] +
			m[13] * m[6] * m[11] -
			m[13] * m[7] * m[10];

		inv[4] = -m[4] * m[10] * m[15] +
			m[4] * m[11] * m[14] +
			m[8] * m[6] * m[15] -
			m[8] * m[7] * m[14] -
			m[12] * m[6] * m[11] +
			m[12] * m[7] * m[10];

		inv[8] = m[4] * m[9] * m[15] -
			m[4] * m[11] * m[13] -
			m[8] * m[5] * m[15] +
			m[8] * m[7] * m[13] +
			m[12] * m[5] * m[11] -
			m[12] * m[7] * m[9];

		inv[12] = -m[4] * m[9] * m[14] +
			m[4] * m[10] * m[13] +
			m[8] * m[5] * m[14] -
			m[8] * m[6] * m[13] -
			m[12] * m[5] * m[10] +
			m[12] * m[6] * m[9];

		inv[1] = -m[1] * m[10] * m[15] +
			m[1] * m[11] * m[14] +
			m[9] * m[2] * m[15] -
			m[9] * m[3] * m[14] -
			m[13] * m[2] * m[11] +
			m[13] * m[3] * m[10];

		inv[5] = m[0] * m[10] * m[15] -
			m[0] * m[11] * m[14] -
			m[8] * m[2] * m[15] +
			m[8] * m[3] * m[14] +
			m[12] * m[2] * m[11] -
			m[12] * m[3] * m[10];

		inv[9] = -m[0] * m[9] * m[15] +
			m[0] * m[11] * m[13] +
			m[8] * m[1] * m[15] -
			m[8] * m[3] * m[13] -
			m[12] * m[1] * m[11] +
			m[12] * m[3] * m[9];

		inv[13] = m[0] * m[9] * m[14] -
			m[0] * m[10] * m[13] -
			m[8] * m[1] * m[14] +
			m[8] * m[2] * m[13] +
			m[12] * m[1] * m[10] -
			m[12] * m[2] * m[9];

		inv[2] = m[1] * m[6] * m[15] -
			m[1] * m[7] * m[14] -
			m[5] * m[2] * m[15] +
			m[5] * m[3] * m[14] +
			m[13] * m[2] * m[7] -
			m[13] * m[3] * m[6];

		inv[6] = -m[0] * m[6] * m[15] +
			m[0] * m[7] * m[14] +
			m[4] * m[2] * m[15] -
			m[4] * m[3] * m[14] -
			m[12] * m[2] * m[7] +
			m[12] * m[3] * m[6];

		inv[10] = m[0] * m[5] * m[15] -
			m[0] * m[7] * m[13] -
			m[4] * m[1] * m[15] +
			m[4] * m[3] * m[13] +
			m[12] * m[1] * m[7] -
			m[12] * m[3] * m[5];

		inv[14] = -m[0] * m[5] * m[14] +
			m[0] * m[6] * m[13] +
			m[4] * m[1] * m[14] -
			m[4] * m[2] * m[13] -
			m[12] * m[1] * m[6] +
			m[12] * m[2] * m[5];

		inv[3] = -m[1] * m[6] * m[11] +
			m[1] * m[7] * m[10] +
			m[5] * m[2] * m[11] -
			m[5] * m[3] * m[10] -
			m[9] * m[2] * m[7] +
			m[9] * m[3] * m[6];

		inv[7] = m[0] * m[6] * m[11] -
			m[0] * m[7] * m[10] -
			m[4] * m[2] * m[11] +
			m[4] * m[3] * m[10] +
			m[8] * m[2] * m[7] -
			m[8] * m[3] * m[6];

		inv[11] = -m[0] * m[5] * m[11] +
			m[0] * m[7] * m[9] +
			m[4] * m[1] * m[11] -
			m[4] * m[3] * m[9] -
			m[8] * m[1] * m[7] +
			m[8] * m[3] * m[5];

		inv[15] = m[0] * m[5] * m[10] -
			m[0] * m[6] * m[9] -
			m[4] * m[1] * m[10] +
			m[4] * m[2] * m[9] +
			m[8] * m[1] * m[6] -
			m[8] * m[2] * m[5];

		det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

		if (det == 0)
			return false;

		det = static_cast<float>(1.0 / det);

		for (i = 0; i < 16; i++)
			invOut[i] = inv[i] * det;

		return true;
	}

public:
	float m[16];

	Mat4(float m00, float m01 = 0, float m02 = 0, float m03 = 0,
		float m10 = 0, float m11 = 1, float m12 = 0, float m13 = 0,
		float m20 = 0, float m21 = 0, float m22 = 1, float m23 = 0,
		float m30 = 0, float m31 = 0, float m32 = 0, float m33 = 1) {
		m[0] = m00; m[1] = m01; m[2] = m02; m[3] = m03;
		m[4] = m10; m[5] = m11; m[6] = m12; m[7] = m13;
		m[8] = m20; m[9] = m21; m[10] = m22; m[11] = m23;
		m[12] = m30; m[13] = m31; m[14] = m32; m[15] = m33;
	}

	Mat4(const float *m) {
		for (int i = 0; i < 16; ++i)
			this->m[i] = m[i];
	}

	float& operator[](int index) {
		assert(0 <= index && index <= 15 && "Mat4 : Not valid index");

		return m[index];
	}

	float operator[](int index) const {
		assert(0 <= index && index <= 15 && "Mat4 : Not valid index");

		return m[index];
	}

	// Identity matrix constructor
	Mat4() {
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				m[i * 4 + j] = (i == j) ? 1.0f : 0.0f;
	}

	const void operator=(const Mat4& right) {
		for (int i = 0; i < 16; ++i)
			this->m[i] = right.m[i];
	}

	Mat4 operator*(const Mat4& right) const {
		Mat4 result;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				result.m[i * 4 + j] = 0;
				for (int k = 0; k < 4; k++) result.m[i * 4 + j] += m[i * 4 + k] * right.m[k * 4 + j];
			}
		}
		return result;
	}

	operator float*() { return &m[0]; }

	Vec4 Mat4::operator*(const Vec4& right) const;

	Mat4 translateM(float x, float y, float z = 0.0f) const {
		Mat4 translationMatrix;
		translationMatrix.m[3] = x;
		translationMatrix.m[7] = y;
		translationMatrix.m[11] = z;

		Mat4 result = *this * translationMatrix;

		return result;
	}

	Mat4 scaleM(float x, float y, float z = 1.0f) const {
		Mat4 scaleMatrix;
		scaleMatrix[0] = x;
		scaleMatrix[5] = y;
		scaleMatrix[10] = z;

		Mat4 result = *this * scaleMatrix;

		return result;
	}

	Mat4 rotate(float xRad, float yRad, float zRad) const {
		Mat4 rotationMatrix;
		rotationMatrix = rotationMatrix.rotateXM(xRad);
		rotationMatrix = rotationMatrix.rotateYM(yRad);
		rotationMatrix = rotationMatrix.rotateZM(zRad);

		Mat4 result = *this * rotationMatrix;

		return result;
	}

	Mat4 rotateZM(float rad) const {
		Mat4 rotationMatrix;
		rotationMatrix[0] = cos(rad);
		rotationMatrix[1] = -sin(rad);
		rotationMatrix[4] = sin(rad);
		rotationMatrix[5] = cos(rad);

		Mat4 result = *this * rotationMatrix;

		return result;

	}

	Mat4 rotateYM(float rad) const {
		Mat4 rotationMatrix;
		rotationMatrix[0] = cos(rad);
		rotationMatrix[2] = sin(rad);
		rotationMatrix[8] = -sin(rad);
		rotationMatrix[10] = cos(rad);

		Mat4 result = *this * rotationMatrix;

		return result;
	}

	Mat4 rotateXM(float rad) const {
		Mat4 rotationMatrix;
		rotationMatrix[5] = cos(rad);
		rotationMatrix[6] = -sin(rad);
		rotationMatrix[9] = sin(rad);
		rotationMatrix[10] = cos(rad);

		Mat4 result = *this * rotationMatrix;

		return result;
	}

	Mat4 rotateZsolt(float rotAngle, float xAxis, float yAxis, float zAxis)
	{
		Mat4 rodriguez
		(
			cos(rotAngle) + xAxis*xAxis*(1 - cos(rotAngle)), yAxis*xAxis*(1 - cos(rotAngle)) + zAxis*sin(rotAngle), zAxis*xAxis*(1 - cos(rotAngle)) - yAxis*sin(rotAngle), 0,
			xAxis*yAxis*(1 - cos(rotAngle)) - zAxis*sin(rotAngle), cos(rotAngle) + yAxis*yAxis*(1 - cos(rotAngle)), zAxis*yAxis*(1 - cos(rotAngle)) + xAxis*sin(rotAngle), 0,
			xAxis*zAxis*(1 - cos(rotAngle)) + yAxis*sin(rotAngle), yAxis*zAxis*(1 - cos(rotAngle)) - xAxis*sin(rotAngle), cos(rotAngle) + zAxis*zAxis*(1 - cos(rotAngle)), 0,
			0, 0, 0, 1
		);
		return rodriguez;
	}

	Mat4 rotateBoldi(float angle, float wx, float wy, float wz) {
		float costheta = cosf(angle);
		float sintheta = sinf(angle);
		return Mat4(costheta + wx * wx * (1 - costheta), wx * wy * (1 - costheta) - wz * sintheta, wx * wz * (1 - costheta) + wy * sintheta, 0.0f,
			wx * wy * (1 - costheta) + wz * sintheta, costheta + wy * wy * (1 - costheta), wy * wz * (1 - costheta) - wx * sintheta, 0.0f,
			wx * wz * (1 - costheta) - wy * sintheta, wy * wz * (1 - costheta) + wx * sintheta, costheta + wz * wz * (1 - costheta), 0.0f,
			0.0f, 0.0f, 0.0f, 1);
	}

	Mat4 invertM() const {
		Mat4 result;
		Mat4::gluInvertMatrix(this->m, result.m);
		return result;
	}

	Mat4 transposeM() const {
		Mat4 result;

		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				result.m[4 * i + j] = this->m[4 * j + i];

		return result;
	}

	static Mat4 perspectiveM(float fovInDegrees, float aspect, float nearDistance, float farDistance) {
		Mat4 result;

		float a = 1 / (tan(fovInDegrees / 2 * 3.1415926545f / 180));

		// Set the values for the perspective which aren't zeroes
		result.m[0] = a / aspect;
		result.m[5] = a;
		result.m[10] = -((farDistance + nearDistance) / (farDistance - nearDistance));

		result.m[14] = -1.0f;

		result.m[11] = -((2.0f * farDistance * nearDistance) / (farDistance - nearDistance));

		return result;
	}

	// returns an orthographic matrix
	// bottom, top, left, right, near, far
	static Mat4 orthoM(float b, float t, float l, float r, float n, float f) {
		Mat4 result;

		result.m[0] = 2 / (r - l);
		result.m[3] = -(r + l) / (r - l);
		result.m[5] = 2 / (t - b);
		result.m[7] = -(t + b) / (t - b);
		result.m[10] = -2 / (f - n);
		result.m[11] = -(f + n) / (f - n);
		result.m[15] = 1.0f;	// Already set

		return result;
	}

	void writeOut() const {
		printf("\t");
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				printf("%.3f ", this->m[i * 4 + j]);
			}
			if (i != 3) printf("\n\t");
			else printf("\n");
		}
	}
};

} //namespace Math