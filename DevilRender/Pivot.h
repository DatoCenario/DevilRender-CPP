#pragma once
#include "Math.h"

namespace std
{
	class Pivot
	{
	private:
		Matrix3x3 localMatrix;
		Matrix3x3 globalMatrix;

		void updLocalMatrix();

		void updGlobalMatrix();

	public:
		float3 xaxis;
		float3 yaxis;
		float3 zaxis;
		float3 center;

		Pivot();

		Pivot(const float3& center, const float3& xaxis, const float3& yaxis, const float3& zaxis);

		Pivot(const float3& center);

		~Pivot();

		float3 toLocalCoords(const float3& f);

		float3 toGlobalCoords(const float3& f);

		void rotatePivot(float angle , char axis);

		void movePivot(const float3& f);
	};
}

