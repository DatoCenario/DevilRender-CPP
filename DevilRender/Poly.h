#pragma once
#include "Geometry.h"

namespace std
{
	class Poly : public Primitive
	{
	public:
		Poly(const float3& center, const float3& v1, const float3& v2, const float3& v3);
		~Poly();
	};
}