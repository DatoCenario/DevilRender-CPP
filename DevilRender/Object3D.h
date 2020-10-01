#pragma once
#include "Math.h"
#include "Pivot.h"


namespace std
{
	class Object3D
	{
	public:
		Object3D()
		{}

		Pivot pivot;

		virtual void move(const float3& f) = 0;

		virtual void rotate(float angle, char axis) = 0;

	};

}
