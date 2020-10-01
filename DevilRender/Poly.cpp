#include "Poly.h"

namespace std
{
	Poly::Poly(const float3& center, const float3& v1, const float3& v2, const float3& v3)
	{
		pivot = Pivot(center);
		localVertices = new vector<float3>
		{
			v1,v2,v3
		};
		globalVertices = new vector<float3>(3);
		updGlobalVertices();
		indexes = new vector<int>{0,1,2};
		normalsIndexes = new vector<int>();
		texCoordsIndexes = new vector<int>();
	}
	Poly::~Poly()
	{
	}
}