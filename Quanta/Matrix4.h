#pragma once
#include "Vector4.h"

class Matrix4
{

public:
	Matrix4();
	Matrix4(float e0, float e4, float e8, float e12,
			float e1, float e5, float e9, float e13,
			float e2, float e6, float e10, float e14,
			float e3, float e7, float e11, float e15);

	Matrix4(bool isScalar, bool isTranslation, bool isRotation, float val1, float val2, float val3);

	Matrix4 operator +(Matrix4 const& obj);
	Matrix4 operator +(int const& obj);
	Matrix4 operator -(Matrix4 const& obj);
	Matrix4 operator -(int const& obj);
	Matrix4 operator *(Matrix4 const& obj);
	Matrix4 operator *(int const& obj);

	Vector4 operator *(Vector4 const& obj);

	float* GetData();

private:
	float m_data[16] = { 0 };
};

