#include "Vector4.h"
#include <math.h>

Vector4::Vector4(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_w = 1.0f;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_w = w;
}


Vector4::Vector4()
{
	m_x = 0.0f;
	m_y = 0.0f;
	m_z = 0.0f;
	m_w = 1.0f;
}

// Cross product
Vector4 Vector4::operator*(Vector4 const& obj)
{
	return (Vector4(m_y * obj.m_z - m_z * obj.m_y,
					m_z * obj.m_x - m_x * obj.m_z,
					m_x * obj.m_y - m_y * obj.m_x));
}

Vector4 Vector4::operator+(Vector4 const& obj)
{
	return (Vector4(m_x + obj.m_x, m_y + obj.m_y, m_z + obj.m_z, m_w + obj.m_w));
}

Vector4 Vector4::operator-(Vector4 const& obj)
{
	return (Vector4(m_x - obj.m_x, m_y - obj.m_y, m_z - obj.m_z, m_w - obj.m_w));
}

Vector4 Vector4::operator*(float const& obj)
{
	return (Vector4(m_x * obj, m_y * obj, m_z * obj, m_w * obj));
}

Vector4 Vector4::operator+(float const& obj)
{
	return (Vector4(m_x + obj, m_y + obj, m_z + obj, m_w + obj));
}

Vector4 Vector4::operator-(float const& obj)
{
	return (Vector4(m_x - obj, m_y - obj, m_z - obj, m_w - obj));
}

float Vector4::GetLength()
{
	return sqrt(m_x * m_x + m_y * m_y + m_z + m_z);
}

Vector4 Vector4::Normalized()
{
	float length = GetLength();
	return Vector4(m_x / length, m_y / length, m_z / length);
}

float Vector4::GetX()
{
	return m_x;
}

float Vector4::GetY()
{
	return m_y;
}

float Vector4::GetZ()
{
	return m_z;
}

float Vector4::GetW()
{
	return m_w;
}

void Vector4::Set(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

void Vector4::Set(float x, float y, float z, float w)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_w = w;
}


