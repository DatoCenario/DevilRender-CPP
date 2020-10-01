
#include "Math.h"
#include <iostream>


namespace std
{
	float2::float2()
	{
	}

	float2::float2(float x)
	{
		this->x = x;
	}

	float2::float2(float x, float y) : float2(x)
	{
		this->y = y;
	}

	float2::~float2()
	{
	}

	float frand()
	{
		return 1 / (float)rand();
	}

	float max(float x, float y)
	{
		if (y > x)
		{
			return y;
		}
		return x;
	}

	int max(int x, int y)
	{
		if (y > x)
		{
			return y;
		}
		return x;
	}

	int min(int x, int y)
	{
		if (y < x)
		{
			return y;
		}
		return x;
	}

	float2 operator + (const float2& f1, const float2& f2)
	{
		return float2(f1.x + f2.x, f1.y + f2.y);
	}

	float2 operator - (const float2& f1, const float2& f2)
	{
		return float2(f1.x - f2.x, f1.y - f2.y);
	}

	float2 operator * (const float2& f1, float k)
	{
		return float2(f1.x * k, f1.y * k);
	}

	float2 operator / (const float2& f1, float k)
	{
		return float2(f1.x / k, f1.y / k);
	}

	float2 operator * (const float& k, const float2& f1)
	{
		return f1 * k;
	}

	float2 operator / (const float& k, const float2& f1)
	{
		return f1 / k;
	}

	float2& float2::operator+= (const float2& f)
	{
		this->x += f.x;
		this->y += f.y;
		return *this;
	}

	float2& float2::operator-= (const float2& f)
	{
		this->x -= f.x;
		this->y -= f.y;
		return *this;
	}

	float2& float2::operator*= (float k)
	{
		this->x *= k;
		this->y *= k;
		return *this;
	}

	float2& float2::operator/= (float k)
	{
		this->x /= k;
		this->y /= k;
		return *this;
	}

	float len(const float2& n)
	{
		return sqrt(n.x * n.x + n.y * n.y);
	}

	float2 normalize(const float2& n)
	{
		return n / len(n);
	}

	float cross(const float2& f1, const float2& f2)
	{
		return f1.x * f2.x + f1.y * f2.y;
	}



	float3::float3()
	{
	}

	float3::float3(float x)
	{
		this->x = x;
	}

	float3::float3(float x, float y) : float3(x)
	{
		this->y = y;
	}

	float3::float3(float x, float y, float z) : float3(x, y)
	{
		this->z = z;
	}

	float3::~float3()
	{
	}

	float3 operator + (const float3& f1, const float3& f2)
	{
		return float3(f1.x + f2.x, f1.y + f2.y, f1.z + f2.z);
	}

	float3 operator - (const float3& f1, const float3& f2)
	{
		return float3(f1.x - f2.x, f1.y - f2.y, f1.z - f2.z);
	}

	float3 operator-(const float3& f1)
	{
		return float3(-f1.x, -f1.y, -f1.z);
	}


	float3 operator * (const float3& f1, float k)
	{
		return float3(f1.x * k, f1.y * k, f1.z * k);
	}

	float3 operator / (const float3& f1, float k)
	{
		return float3(f1.x / k, f1.y / k, f1.z / k);
	}

	float3 operator * (const float& k, const float3& f1)
	{
		return f1 * k;
	}

	float3 operator / (const float& k, const float3& f1)
	{
		return f1 / k;
	}

	float3& float3::operator+= (const float3& f)
	{
		this->x += f.x;
		this->y += f.y;
		this->z += f.z;
		return *this;
	}

	float3& float3::operator-= (const float3& f)
	{
		this->x -= f.x;
		this->y -= f.y;
		this->z -= f.z;
		return *this;
	}

	float3& float3::operator*= (float k)
	{
		this->x *= k;
		this->y *= k;
		this->z *= k;
		return *this;
	}

	float3& float3::operator/= (float k)
	{
		this->x /= k;
		this->y /= k;
		this->z /= k;
		return *this;
	}

	float len(const float3& n)
	{
		return sqrt(n.x * n.x + n.y * n.y + n.z * n.z);
	}

	float3 normalize(const float3& n)
	{
		return n / len(n);
	}

	float cross(const float3& f1, const float3& f2)
	{
		return f1.x * f2.x + f1.y * f2.y + f1.z * f2.z;
	}

	float angle(const float3& f1, const float3& f2)
	{
		return acos(cross(f1, f2) / (len(f1) * len(f2)));
	}

	Matrix3x3::Matrix3x3()
	{
	}

	Matrix3x3::Matrix3x3(
		float a11,
		float a12,
		float a13,
		float a21,
		float a22,
		float a23,
		float a31,
		float a32,
		float a33)
	{
		this->a11 = a11;
		this->a12 = a12;
		this->a13 = a13;
		this->a21 = a21;
		this->a22 = a22;
		this->a23 = a23;
		this->a31 = a31;
		this->a32 = a32;
		this->a33 = a33;
	}

	Matrix3x3::~Matrix3x3()
	{
	}

	float3 transform(const Matrix3x3& m, const float3& f)
	{
		return float3(
			m.a11 * f.x + m.a12 * f.y + m.a13 * f.z,
			m.a21 * f.x + m.a22 * f.y + m.a23 * f.z,
			m.a31 * f.x + m.a32 * f.y + m.a33 * f.z
		);
	}

	Matrix3x3 getRotation(float angle, char axis)
	{
		switch (axis)
		{
		case 'x':
			return Matrix3x3(0, 0, 1, 0, cos(angle), -sin(angle), 0, sin(angle), cos(angle));
			break;
		case 'y':
			return Matrix3x3(cos(angle), 0, -sin(angle), 0, 1, 0, sin(angle), 0, cos(angle));
			break;
		case 'z':
			return Matrix3x3(cos(angle), -sin(angle), 0, sin(angle), cos(angle), 0, 0, 0, 1);
			break;
		}
	}


	float3 rotate(const float3& f, float angle, char axis)
	{
		return transform(getRotation(angle, axis), f);
	}

	float3 move(const float3& f, float x, float y, float  z)
	{
		return float3(f.x + x, f.y + y, f.z + z);
	}

	void fswap(float& f1, float& f2)
	{
		float temp = f1;
		f1 = f2;
		f2 = temp;
	}

	void f2swap(float2& f1, float2& f2)
	{
		float2 temp = f1;
		f1 = f2;
		f2 = temp;
	}
	void f3swap(float3& f1, float3& f2)
	{
		float3 temp = f1;
		f1 = f2;
		f2 = temp;
	}
	float3 proection(const float3& f1, const float3& f2)
	{
		return f2 * cross(f1, f2) / cross(f2,f2);
	}
}