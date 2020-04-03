#include "Matrix4.h"
#include <math.h>

// Initialize matrix as an identity matrix
Matrix4::Matrix4()
{
	// 4x4 Matrix which goes columns then rows, ie:
	// 1  5  9  13
	// 2  6  10 14
	// 3  7  11 15
	// 4  8  12 16

	m_data[0] = 1;
	m_data[1] = 0;
	m_data[2] = 0;
	m_data[3] = 0;

	m_data[4] = 0;
	m_data[5] = 1;
	m_data[6] = 0;
	m_data[7] = 0;

	m_data[8] = 0;
	m_data[9] = 0;
	m_data[10] = 1;
	m_data[11] = 0;

	m_data[12] = 0;
	m_data[13] = 0;
	m_data[14] = 0;
	m_data[15] = 1;
}

Matrix4::Matrix4(float e0, float e4, float e8, float e12, float e1, float e5, float e9, float e13, float e2, float e6, float e10, float e14, float e3, float e7, float e11, float e15)
{
	m_data[0] = e0;
	m_data[1] = e1;
	m_data[2] = e2;
	m_data[3] = e3;

	m_data[4] = e4;
	m_data[5] = e5;
	m_data[6] = e6;
	m_data[7] = e7;

	m_data[8] = e8;
	m_data[9] = e9;
	m_data[10] = e10;
	m_data[11] = e11;

	m_data[12] = e12;
	m_data[13] = e13;
	m_data[14] = e14;
	m_data[15] = e15;
}

Matrix4::Matrix4(bool isScalar, bool isTranslation, bool isRotation, float val1, float val2, float val3)
{
	if (isScalar)
	{
		m_data[0] = val1;
		m_data[1] = 0;
		m_data[2] = 0;
		m_data[3] = 0;

		m_data[4] = 0;
		m_data[5] = val2;
		m_data[6] = 0;
		m_data[7] = 0;

		m_data[8] = 0;
		m_data[9] = 0;
		m_data[10] = val3;
		m_data[11] = 0;

		m_data[12] = 0;
		m_data[13] = 0;
		m_data[14] = 0;
		m_data[15] = 1;
	}
	else if (isTranslation)
	{
		m_data[0] = 1;
		m_data[1] = 0;
		m_data[2] = 0;
		m_data[3] = 0;

		m_data[4] = 0;
		m_data[5] = 1;
		m_data[6] = 0;
		m_data[7] = 0;

		m_data[8] = 0;
		m_data[9] = 0;
		m_data[10] = 1;
		m_data[11] = 0;

		m_data[12] = val1;
		m_data[13] = val2;
		m_data[14] = val3;
		m_data[15] = 1;
	}
	else if (isRotation)
	{
		// Rotate on X
		if (val1 > 0)
		{
			m_data[0] = 1;
			m_data[1] = 0;
			m_data[2] = 0;
			m_data[3] = 0;

			m_data[4] = 0;
			m_data[5] = cos(val1);
			m_data[6] = sin(val1);
			m_data[7] = 0;

			m_data[8] = 0;
			m_data[9] = -sin(val1);
			m_data[10] = cos(val1);
			m_data[11] = 0;

			m_data[12] = 0;
			m_data[13] = 0;
			m_data[14] = 0;
			m_data[15] = 1;
		}
		// Rotate on Y
		else if (val2 > 0)
		{
			m_data[0] = cos(val2);
			m_data[1] = 0;
			m_data[2] = -sin(val2);
			m_data[3] = 0;

			m_data[4] = 0;
			m_data[5] = 1;
			m_data[6] = 0;
			m_data[7] = 0;

			m_data[8] = sin(val2);
			m_data[9] = 0;
			m_data[10] = cos(val2);
			m_data[11] = 0;

			m_data[12] = 0;
			m_data[13] = 0;
			m_data[14] = 0;
			m_data[15] = 1;
		}
		// Rotate on Z
		else if (val3 > 0)
		{
			m_data[0] = cos(val3);
			m_data[1] = sin(val3);
			m_data[2] = 0;
			m_data[3] = 0;

			m_data[4] = -sin(val3);
			m_data[5] = cos(val3);
			m_data[6] = 0;
			m_data[7] = 0;

			m_data[8] = 0;
			m_data[9] = 0;
			m_data[10] = 1;
			m_data[11] = 0;

			m_data[12] = 0;
			m_data[13] = 0;
			m_data[14] = 0;
			m_data[15] = 1;
		}
		else
		{
			m_data[0] = 1;
			m_data[1] = 0;
			m_data[2] = 0;
			m_data[3] = 0;

			m_data[4] = 0;
			m_data[5] = 1;
			m_data[6] = 0;
			m_data[7] = 0;

			m_data[8] = 0;
			m_data[9] = 0;
			m_data[10] = 1;
			m_data[11] = 0;

			m_data[12] = 0;
			m_data[13] = 0;
			m_data[14] = 0;
			m_data[15] = 1;
		}
	}
	else
	{
		m_data[0] = val1;
		m_data[1] = 0;
		m_data[2] = 0;
		m_data[3] = 0;

		m_data[4] = val2;
		m_data[5] = 0;
		m_data[6] = 0;
		m_data[7] = 0;

		m_data[8] = val3;
		m_data[9] = 0;
		m_data[10] = 0;
		m_data[11] = 0;

		m_data[12] = 1;
		m_data[13] = 0;
		m_data[14] = 0;
		m_data[15] = 0;
	}
}


Matrix4 Matrix4::operator+(Matrix4 const& obj)
{
	return Matrix4(m_data[0] + obj.m_data[0], m_data[4] + obj.m_data[4], m_data[8] + obj.m_data[8], m_data[12] + obj.m_data[12],
					m_data[1] + obj.m_data[1], m_data[5] + obj.m_data[5], m_data[9] + obj.m_data[9], m_data[13] + obj.m_data[13],
					m_data[2] + obj.m_data[2], m_data[6] + obj.m_data[6], m_data[10] + obj.m_data[10], m_data[14] + obj.m_data[14],
					m_data[3] + obj.m_data[3], m_data[7] + obj.m_data[7], m_data[11] + obj.m_data[11], m_data[15] + obj.m_data[15]);
}

Matrix4 Matrix4::operator+(int const& obj)
{
	return Matrix4(m_data[0] + obj, m_data[4] + obj, m_data[8] + obj, m_data[12] + obj,
					m_data[1] + obj, m_data[5] + obj, m_data[9] + obj, m_data[13] + obj,
					m_data[2] + obj, m_data[6] + obj, m_data[10] + obj, m_data[14] + obj,
					m_data[3] + obj, m_data[7] + obj, m_data[11] + obj, m_data[15] + obj);
}

Matrix4 Matrix4::operator-(Matrix4 const& obj)
{
	return Matrix4(m_data[0] - obj.m_data[0], m_data[4] - obj.m_data[4], m_data[8] - obj.m_data[8], m_data[12] - obj.m_data[12],
					m_data[1] - obj.m_data[1], m_data[5] - obj.m_data[5], m_data[9] - obj.m_data[9], m_data[13] - obj.m_data[13],
					m_data[2] - obj.m_data[2], m_data[6] - obj.m_data[6], m_data[10] - obj.m_data[10], m_data[14] - obj.m_data[14],
					m_data[3] - obj.m_data[3], m_data[7] - obj.m_data[7], m_data[11] - obj.m_data[11], m_data[15] - obj.m_data[15]);
}

Matrix4 Matrix4::operator-(int const& obj)
{
	return Matrix4(m_data[0] - obj, m_data[4] - obj, m_data[8] - obj, m_data[12] - obj,
					m_data[1] - obj, m_data[5] - obj, m_data[9] - obj, m_data[13] - obj,
					m_data[2] - obj, m_data[6] - obj, m_data[10] - obj, m_data[14] - obj,
					m_data[3] - obj, m_data[7] - obj, m_data[11] - obj, m_data[15] - obj);
}

Matrix4 Matrix4::operator*(Matrix4 const& obj)
{
	return Matrix4(m_data[0] * obj.m_data[0] + m_data[4] * obj.m_data[1] + m_data[8] * obj.m_data[2] + m_data[12] * obj.m_data[3],
					m_data[0] * obj.m_data[4] + m_data[4] * obj.m_data[5] + m_data[8] * obj.m_data[6] + m_data[12] * obj.m_data[7],
					m_data[0] * obj.m_data[8] + m_data[4] * obj.m_data[9] + m_data[8] * obj.m_data[10] + m_data[12] * obj.m_data[11],
					m_data[0] * obj.m_data[12] + m_data[4] * obj.m_data[13] + m_data[8] * obj.m_data[14] + m_data[12] * obj.m_data[15],

					m_data[1] * obj.m_data[0] + m_data[5] * obj.m_data[1] + m_data[9] * obj.m_data[2] + m_data[13] * obj.m_data[3],
					m_data[1] * obj.m_data[4] + m_data[5] * obj.m_data[5] + m_data[9] * obj.m_data[6] + m_data[13] * obj.m_data[7],
					m_data[1] * obj.m_data[8] + m_data[5] * obj.m_data[9] + m_data[9] * obj.m_data[10] + m_data[13] * obj.m_data[11],
					m_data[1] * obj.m_data[12] + m_data[5] * obj.m_data[13] + m_data[9] * obj.m_data[14] + m_data[13] * obj.m_data[15],

					m_data[2] * obj.m_data[0] + m_data[6] * obj.m_data[1] + m_data[10] * obj.m_data[2] + m_data[14] * obj.m_data[3],
					m_data[2] * obj.m_data[4] + m_data[6] * obj.m_data[5] + m_data[10] * obj.m_data[6] + m_data[14] * obj.m_data[7],
					m_data[2] * obj.m_data[8] + m_data[6] * obj.m_data[9] + m_data[10] * obj.m_data[10] + m_data[14] * obj.m_data[11],
					m_data[2] * obj.m_data[12] + m_data[6] * obj.m_data[13] + m_data[10] * obj.m_data[14] + m_data[14] * obj.m_data[15],

					m_data[3] * obj.m_data[0] + m_data[7] * obj.m_data[1] + m_data[11] * obj.m_data[2] + m_data[15] * obj.m_data[3],
					m_data[3] * obj.m_data[4] + m_data[7] * obj.m_data[5] + m_data[11] * obj.m_data[6] + m_data[15] * obj.m_data[7],
					m_data[3] * obj.m_data[8] + m_data[7] * obj.m_data[9] + m_data[11] * obj.m_data[10] + m_data[15] * obj.m_data[11],
					m_data[3] * obj.m_data[12] + m_data[7] * obj.m_data[13] + m_data[11] * obj.m_data[14] + m_data[15] * obj.m_data[15]);
}

Matrix4 Matrix4::operator*(int const& obj)
{
	return Matrix4(m_data[0] * obj, m_data[4] * obj, m_data[8] * obj, m_data[12] * obj,
					m_data[1] * obj, m_data[5] * obj, m_data[9] * obj, m_data[13] * obj,
					m_data[2] * obj, m_data[6] * obj, m_data[10] * obj, m_data[14] * obj,
					m_data[3] * obj, m_data[7] * obj, m_data[11] * obj, m_data[15] * obj);
}

Vector4 Matrix4::operator*(Vector4 const& obj)
{
	return Vector4(m_data[0] * obj.m_x + m_data[4] * obj.m_y + m_data[8] * obj.m_z + m_data[12] * obj.m_w,
					m_data[1] * obj.m_x + m_data[5] * obj.m_y + m_data[9] * obj.m_z + m_data[13] * obj.m_w,
					m_data[2] * obj.m_x + m_data[6] * obj.m_y + m_data[10] * obj.m_z + m_data[14] * obj.m_w,
					m_data[3] * obj.m_x + m_data[7] * obj.m_y + m_data[11] * obj.m_z + m_data[15] * obj.m_w);
}

float* Matrix4::GetData()
{
	return m_data;
}
