#pragma once
#include "Geometry.h"

namespace std
{
	class Cube : public Primitive
	{
	public:
		Cube(const float3& center, float sideLen);

		~Cube();
	};
}
