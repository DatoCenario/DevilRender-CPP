#pragma once

namespace std
{
	float frand();

	float max(float x, float y);
	int max(int x, int y);
	int min(int x, int y);

	struct float2
	{
		float x;
		float y;

		float2();

		float2(float x);

		float2(float x, float y);

		~float2();

		float2& operator -= (const float2& f);

		float2& operator += (const float2& f);

		float2& operator *= (float k);

		float2& operator /= (float k);
	};

	float2 operator + (const float2& f1, const float2& f2);

	float2 operator - (const float2& f1, const float2& f2);

	float2 operator * (const float2& f1, float k);

	float2 operator / (const float2& f1, float k);

	float2 operator * (const float& k, const float2& f1);

	float2 operator / (const float& k, const float2& f1);

	float len(const float2& n);

	float2 normalize(const float2& n);

	float cross(const float2& f1, const float2& f2);

	struct float3
	{
		float x;
		float y;
		float z;

		float3();

		float3(float x);

		float3(float x, float y);

		float3(float x, float y, float z);

		~float3();

		float3& operator -= (const float3& f);

		float3& operator += (const float3& f);

		float3& operator *= (float k);

		float3& operator /= (float k);
	};

	float3 operator + (const float3& f1, const float3& f2);

	float3 operator - (const float3& f1, const float3& f2);

	float3 operator - (const float3& f1);

	float3 operator * (const float3& f1, float k);

	float3 operator / (const float3& f1, float k);

	float3 operator * (const float& k, const float3& f1);

	float3 operator / (const float& k, const float3& f1);

	float len(const float3& n);

	float3 normalize(const float3& n);

	float cross(const float3& f1, const float3& f2);

	float angle(const float3& f1, const float3& f2);

	struct Matrix3x3
	{
		float a11, a12, a13, a21, a22, a23, a31, a32, a33;

		Matrix3x3();

		Matrix3x3(
			float a11,
			float a12,
			float a13,
			float a21,
			float a22,
			float a23,
			float a31,
			float a32,
			float a33);
		~Matrix3x3();
	};

	float3 transform(const Matrix3x3& m, const float3& f);

	Matrix3x3 getRotation(float angle, char axis);

	float3 rotate(const float3& f, float angle, char axis);

	float3 move(const float3& f, float x, float y, float  z);

	void fswap(float& f1, float& f2);
	void f2swap(float2& f1, float2& f2);
	void f3swap(float3& f1, float3& f2);

	float3 proection(const float3& f1 , const float3& f2);
}