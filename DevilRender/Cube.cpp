#include "Cube.h"


namespace std
{
	Cube::Cube(const float3& center, float sideLen) : Primitive()
	{
		pivot = Pivot(center);
		float d = sideLen / 2;
		localVertices = new vector<float3>(8);
		globalVertices = new  vector<float3>(8);
		normals = new vector<float3>(6);
		normalsIndexes = new vector<int>(36);

		int k = 0;
		for (int i = -1; i <= 1; i += 2)
		{
			for (int g = -1; g <= 1; g += 2)
			{
				for (int h = -1; h <= 1; h += 2)
				{
					float3 local(d * i, d * g, d * h);
					float3 global = pivot.toGlobalCoords(local);
					localVertices->at(k) = local;
					globalVertices->at(k) = global;
					k++;
				}
			}
		}

		normals = new vector<float3>
		{
			float3(1,0,0),
			float3(-1,0,0),
			float3(0,1,0),
			float3(0,-1,0),
			float3(0,0,1) ,
			float3(0,0,-1)
		};

		indexes = new vector<int>
		{
			0,1,3,0,2,3,0,1,5,0,4,5,4,5,7,4,6,7,2,3,7,2,6,7,0,2,6,0,4,6,1,3,7,1,5,7
		};

		normalsIndexes = new vector<int>
		{
			1,1,1,1,1,1,3,3,3,3,3,3,0,0,0,0,0,0,2,2,2,2,2,2,5,5,5,5,5,5,4,4,4,4,4,4
		};

		textureCoods = new vector<float2>();
		texCoordsIndexes = new vector<int>();

	}

	Cube::~Cube()
	{
	}
}