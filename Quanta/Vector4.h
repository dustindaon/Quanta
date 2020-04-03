#pragma once
class Vector4
{
public:
	Vector4(float x, float y, float z);
	Vector4(float x, float y, float z, float w);
	Vector4();

	Vector4 operator * (Vector4 const& obj);
	Vector4 operator + (Vector4 const& obj);
	Vector4 operator - (Vector4 const& obj);
	Vector4 operator * (float const& obj);
	Vector4 operator + (float const& obj);
	Vector4 operator - (float const& obj);

	float GetLength();
	Vector4 Normalized();

	float GetX();
	float GetY();
	float GetZ();
	float GetW();

	void Set(float x, float y, float z);
	void Set(float x, float y, float z, float w);

	float m_x;
	float m_y;
	float m_z;
	float m_w;
private:

};

